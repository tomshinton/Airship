// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "AirController.generated.h"

class UAirHUDBase;
class UInteractionComponent;

UCLASS(MinimalAPI)
class AAirController : public APlayerController
{
	GENERATED_BODY()

	AAirController();

public:

	UPROPERTY()
	UInteractionComponent* InteractionComponent;

	AIRCORE_API void SetMouseVisible(const bool InVisibility);
	AIRCORE_API bool GetMouseVisible() const;

	UAirHUDBase* GetHudWidget() const;

private:

	bool MouseVisible;
};
