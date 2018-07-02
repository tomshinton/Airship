// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AirWidget.h"
#include "AirGameMode.generated.h"

/**
 * 
 */
UCLASS()
class AIRSHIP_API AAirGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AAirGameMode();

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAirWidget> HUDWidgetClass;
	UPROPERTY()
	UAirWidget* SpawnedHUD;

protected:
	virtual void BeginPlay() override;
};
