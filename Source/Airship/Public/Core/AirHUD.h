// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AirWidget.h"
#include "AirHUD.generated.h"

class UAirWidget;

UCLASS()
class AIRSHIP_API AAirHUD : public AHUD
{
	GENERATED_BODY()

	AAirHUD(const FObjectInitializer& ObjectInitializer);
};
