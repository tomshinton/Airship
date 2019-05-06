// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "AirHUD.generated.h"

class UAirHUDBase;

UCLASS(MinimalAPI)
class AAirHUD : public AHUD
{
	GENERATED_BODY()

	AAirHUD(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void BeginPlay() override;

	UPROPERTY()
	UAirHUDBase* HUDWidget;
};
