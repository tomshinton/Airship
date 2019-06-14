// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "AirController.generated.h"

class UInteractionComponent;

UCLASS()
class AAirController : public APlayerController
{
	GENERATED_BODY()

	AAirController();

public:

	UPROPERTY()
	UInteractionComponent* InteractionComponent;
};
