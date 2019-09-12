// Airship Project - Tom Shinton 2018

#include "HealthComponent.h"
#include "ConstructorHelpers.h"
#include "AirChar.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, Log, Log);

UHealthComponent::UHealthComponent()
	: OnHealthChanged()
	, OnHealthDepleted()
	, FallDamageCurve(nullptr)
	, DamageHistory()
	, DamageHistoryLimit(5)
	, MaxHealth(100.f)
	, CurrentHealth(MaxHealth)
	, MaxZVelocity(2500.f)
	, MaxFallDamage(MaxHealth)
	, RegenCooldown(5.f)
	, RegenFrequency(1.f)
	, RegenAmount(1.f)
	, RegenHandle()
{
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> FallDamageCurveRef(TEXT("CurveFloat'/Game/Data/Curves/C_FallDamageCurve.C_FallDamageCurve'"));
	if (FallDamageCurveRef.Object)
	{
		FallDamageCurve = FallDamageCurveRef.Object;
	}
}

void UHealthComponent::BeginPlay()
{
	if (AAirChar* OwningChar = Cast<AAirChar>(GetOwner()))
	{
		OwningChar->OnCharLanded.AddDynamic(this, &UHealthComponent::TakeFallDamage);
	}

	
	Super::BeginPlay();
}

void UHealthComponent::ApplyDamage(const FDamagedEvent& InDamageEvent)
{
	if (FMath::IsNearlyZero(InDamageEvent.Amount))
	{
		return;
	}

	//Modify by type will approriately clamp the value to Min/Max health
	FDamagedEvent ModifiableDamageEvent = InDamageEvent;
	CurrentHealth = ModifyByType(ModifiableDamageEvent);

	DamageHistory.Insert(ModifiableDamageEvent, 0);
	if (DamageHistory.Num() > DamageHistoryLimit)
	{
		DamageHistory.RemoveAt(DamageHistoryLimit);

	}

	OnHealthChanged.Broadcast(ModifiableDamageEvent);

	if (CurrentHealth <= 0.f)
	{
		OnHealthDepleted.Broadcast(ModifiableDamageEvent);
	}
	else
	{
		StartRegenCoundown();
	}
}

void UHealthComponent::RestoreHealth(const FHealEvent& InHealEvent)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + InHealEvent.Amount, 0.f, MaxHealth);

	if (CurrentHealth >= MaxHealth)
	{
		OnHealthRestored.Broadcast();

		StopRegen();
	}

	OnHealthChanged.Broadcast(InHealEvent);
}

void UHealthComponent::TakeFallDamage()
{
	FDamagedEvent FallingDamageEvent(FMath::RandRange(0, 100), EDamageType::Falling, this);
	ApplyDamage(FallingDamageEvent);
}

float UHealthComponent::ModifyByType(FDamagedEvent& InDamageEvent) const
{
	float ModifiedAmount = 0.f;

	if (AActor* Owner = GetOwner())
	{
		switch (InDamageEvent.DamageType)
		{

		case EDamageType::Flat:
			ModifiedAmount = InDamageEvent.Amount;
		break;

		case EDamageType::Falling:
			if (FallDamageCurve)
			{
				const float NormalisedVelocity = FMath::Abs(Owner->GetVelocity().Z) / MaxZVelocity;
				ModifiedAmount = FallDamageCurve->GetFloatValue(NormalisedVelocity) * MaxFallDamage;
			}
		break;

		}
	}

	InDamageEvent.Amount = ModifiedAmount;
	return FMath::Clamp(CurrentHealth - ModifiedAmount, 0.f, MaxHealth);
}

void UHealthComponent::StartRegenCoundown()
{
	if (UWorld* World = GetWorld())
	{
 		FTimerDelegate OnRegenStart;
		OnRegenStart.BindLambda([this, World]()
		{
			World->GetTimerManager().SetTimer(RegenHandle, this, &UHealthComponent::Regen, RegenFrequency, true, RegenFrequency);
		});

		UE_LOG(HealthComponentLog, Log, TEXT("Starting Regen"));
		World->GetTimerManager().SetTimer(RegenHandle, OnRegenStart, RegenCooldown, false, RegenCooldown);
	}
}

void UHealthComponent::Regen()
{
	RestoreHealth(FHealEvent(RegenAmount, EHealType::Regen, this));
}

void UHealthComponent::StopRegen()
{
	if (UWorld* World = GetWorld())
	{
		FTimerManager& TimerManager = World->GetTimerManager();

		if (TimerManager.IsTimerActive(RegenHandle))
		{
			UE_LOG(HealthComponentLog, Log, TEXT("Stopping Regen"));
			TimerManager.ClearTimer(RegenHandle);
		}
	}
}
