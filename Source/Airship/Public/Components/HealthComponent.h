// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthInterface.h"
#include "Events/DamageEvents.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthDepleted, FBaseDamageEvent, KillingBlow);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIRSHIP_API UHealthComponent : public UActorComponent, public IHealthInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();	

private:
	float MaxHealth;
	float CurrentHealth;

	TArray<FBaseDamageEvent> DamageHistory;
	int32 DamageHistoryLimit;

	float MaxZVelocity;
	float MaxFallDamage;

	//HealthInterface
public:
	virtual void ApplyDamage(const FBaseDamageEvent& InDamageEvent) override;
	//HealthInterface

	UFUNCTION()
	void TakeFallDamage();

	float ModifyByType(const FBaseDamageEvent& InDamageEvent);


	virtual void BeginPlay() override;

public:
	FOnHealthDepleted OnHealthDelepled;

private:
	UCurveFloat* FallDamageCurve;

};
