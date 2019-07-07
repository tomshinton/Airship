// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HealthInterface.h"

#include "HealthComponent.generated.h"

UCLASS(MinimalAPI)
class UHealthComponent : public UActorComponent, public IHealthInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();	

	AIRCORE_API TArray<FBaseDamageEvent> GetDamageHistory() const { return DamageHistory; };

#if WITH_DEV_AUTOMATION_TESTS
	void SetFallDamageCurve(UCurveFloat* InNewCurve) { FallDamageCurve = InNewCurve; };
	void SetDamageHistoryLimit(const int32& NewLimit) { DamageHistoryLimit = NewLimit; };
	void ResetToNewMaxHealth(const float& NewMaxHealth)
	{
		MaxHealth = NewMaxHealth;
		CurrentHealth = NewMaxHealth;
	}
	float GetMaxSupportedVelocity() const { return MaxZVelocity; };
#endif //WITH_DEV_AUTOMATION_TESTS

private:

	virtual void BeginPlay() override;

	//HealthInterface
	virtual void ApplyDamage(const FBaseDamageEvent& InDamageEvent) override;
	virtual FOnHealthChanged& GetOnHealthChangedEvent() override { return OnHealthChanged; };
	virtual FOnHealthDepleted& GetOnHealthDepletedEvent() override { return OnHealthDepleted; };
	virtual FOnHealthRestored& GetOnHealthRestoredEvent() override { return OnHealthRestored; };

	virtual float GetMaxHealth() const override { return MaxHealth; };
	virtual float GetCurrentHealth() const override { return CurrentHealth; };
	//~HealthInterface

	UFUNCTION()
	void TakeFallDamage();

	float ModifyByType(FBaseDamageEvent& InDamageEvent) const;

	FOnHealthChanged OnHealthChanged;
	FOnHealthDepleted OnHealthDepleted;
	FOnHealthRestored OnHealthRestored;

	UPROPERTY()
	UCurveFloat* FallDamageCurve;

	TArray<FBaseDamageEvent> DamageHistory;

	int32 DamageHistoryLimit;

	float MaxHealth;
	float CurrentHealth;

	float MaxZVelocity;
	float MaxFallDamage;
};
