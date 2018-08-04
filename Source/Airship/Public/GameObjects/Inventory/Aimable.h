// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjects/Inventory/WorldItem.h"
#include "Scope.h"
#include "Aimable.generated.h"


UCLASS()
class AIRSHIP_API AAimable : public AWorldItem
{
	GENERATED_BODY()

	AAimable();

public:

	UPROPERTY(EditDefaultsOnly, Category = Scope)
	UScope* Scope;

	UPROPERTY(EditDefaultsOnly, Category = Scope)
	bool UseScope;

	UPROPERTY(EditDefaultsOnly, Category = Scope)
	float BlendTime;

	UPROPERTY(EditDefaultsOnly, Category = Scope)
	float BlendExp;

public:
	virtual void StartPrimary() override;
	virtual void EndPrimary() override;
	virtual void StartSecondary() override;
	virtual void EndSecondary() override;
};
