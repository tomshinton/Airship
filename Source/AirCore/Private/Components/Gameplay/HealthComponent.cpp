// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "ConstructorHelpers.h"
#include "AirChar.h"

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
{
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> FallDamageCurveRef(TEXT("CurveFloat'/Game/Data/Curves/C_FallDamageCurve.C_FallDamageCurve'"));
	if (FallDamageCurveRef.Object)
	{
		FallDamageCurve = FallDamageCurveRef.Object;
	}
}

void UHealthComponent::ApplyDamage(const FBaseDamageEvent& InDamageEvent)
{
	//Modify by type will approriately clamp the value to Min/Max health
	FBaseDamageEvent ModifiableDamageEvent = InDamageEvent;
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
}

void UHealthComponent::TakeFallDamage()
{
	FBaseDamageEvent FallingDamageEvent(FMath::RandRange(0, 100), EDamageType::Falling, this);
	ApplyDamage(FallingDamageEvent);
}

float UHealthComponent::ModifyByType(FBaseDamageEvent& InDamageEvent) const
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

void UHealthComponent::BeginPlay()
{
	if (AAirChar* OwningChar = Cast<AAirChar>(GetOwner()))
	{
		OwningChar->OnCharLanded.AddDynamic(this, &UHealthComponent::TakeFallDamage);
	}

	Super::BeginPlay();
}



