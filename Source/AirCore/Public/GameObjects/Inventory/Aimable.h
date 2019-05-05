// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjects/Inventory/WorldItem.h"
#include "Scope.h"
#include "Aimable.generated.h"

//////////////////////////////////////////////////////////////////////////
// Base class for anything that can be fired/aimed
//////////////////////////////////////////////////////////////////////////

UCLASS()
class AAimable : public AWorldItem
{
	GENERATED_BODY()

	AAimable();

public:

	static const float MaxFireDistance;

	UPROPERTY(EditDefaultsOnly, Category = Actions)
	bool UseScope;

	UPROPERTY(EditDefaultsOnly, Category = Actions)
	bool IsFirable;

	UPROPERTY(EditDefaultsOnly, Category = Scope, meta = (EditCondition = "UseScope"))
	UScope* Scope;

	UPROPERTY(EditDefaultsOnly, Category = Firing, meta = (EditCondition = "IsFirable"))
	int32 FireCost;

	UPROPERTY(EditDefaultsOnly, Category = Scope, meta = (EditCondition = "UseScope"))
	float BlendTime;

	UPROPERTY(EditDefaultsOnly, Category = Scope, meta = (EditCondition = "UseScope"))
	float BlendExp;

	virtual void StartFire();
	virtual void EndFire();

public:
	virtual void StartPrimary() override;
	virtual void EndPrimary() override;
	virtual void StartSecondary() override;
	virtual void EndSecondary() override;

private:

	FVector GetFireDirection() const;

	bool HasFired;
};
