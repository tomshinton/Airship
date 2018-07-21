// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjects/Inventory/WorldItem.h"
#include "Aimable.generated.h"


UCLASS()
class AIRSHIP_API AAimable : public AWorldItem
{
	GENERATED_BODY()
	
public:
	virtual void StartPrimary() override;
	virtual void EndPrimary() override;
	virtual void StartSecondary() override;
	virtual void EndSecondary() override;
};
