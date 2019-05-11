// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "ConstructorHelpers.h"
#include "AirChar.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
	: MaxHealth(100.f)
	, CurrentHealth(MaxHealth)
	, DamageHistoryLimit(5)
	, MaxZVelocity(2500.f)
	, MaxFallDamage(MaxHealth)
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> FallDamageCurveRef(TEXT("CurveFloat'/Game/Data/Curves/C_FallDamageCurve.C_FallDamageCurve'"));
	if (FallDamageCurveRef.Object)
	{
		FallDamageCurve = FallDamageCurveRef.Object;
	}
}

void UHealthComponent::ApplyDamage(const FBaseDamageEvent& InDamageEvent)
{
	CurrentHealth = FMath::Clamp((CurrentHealth - ModifyByType(InDamageEvent)), 0.f, MaxHealth);

	DamageHistory.Insert(InDamageEvent, 0);
	if (DamageHistory.Num() > DamageHistoryLimit)
	{
		DamageHistory.RemoveAt(DamageHistoryLimit);
	}

	if (CurrentHealth <= 0.f)
	{
		OnHealthDelepled.Broadcast(DamageHistory[0]);
	}
}

void UHealthComponent::TakeFallDamage()
{
	FBaseDamageEvent FallingDamageEvent(FMath::RandRange(0, 100), EDamageType::Falling, this);
	ApplyDamage(FallingDamageEvent);
}

float UHealthComponent::ModifyByType(const FBaseDamageEvent& InDamageEvent)
{
	switch (InDamageEvent.DamageType)
	{
	case EDamageType::Falling:
		if (FallDamageCurve)
		{
			const float NormalisedVelocity = FMath::Abs(GetOwner()->GetVelocity().Z) / MaxZVelocity;
			return FallDamageCurve->GetFloatValue(NormalisedVelocity) * MaxFallDamage;
		}
	break;
	}

	return InDamageEvent.Amount;
}

void UHealthComponent::BeginPlay()
{
	if (AAirChar* OwningChar = Cast<AAirChar>(GetOwner()))
	{
		OwningChar->OnCharLanded.AddDynamic(this, &UHealthComponent::TakeFallDamage);
	}
}

