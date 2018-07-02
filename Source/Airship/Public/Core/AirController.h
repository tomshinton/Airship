// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "AirController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLookAtChange, AActor*, NewLookAt);

DECLARE_STATS_GROUP(TEXT("ControllerLookAt"), STATGROUP_ControllerFunctions, STATCAT_Advanced);

UCLASS()
class AIRSHIP_API AAirController : public APlayerController
{
	GENERATED_BODY()

	AAirController();

public:
	virtual void Possess(APawn* aPawn) override;

	FOnLookAtChange OnLookAtChanged;

private:
	void LookAt();
	bool TraceSceneChanged();

	AActor* LastLookAtActor;
	AActor* CurrentLookAtActor;

	FTransform CachedObjectTransform;
	FTransform CachedPawnTransform;

	FTimerHandle LookAtTimerHandle;
	float LookAtFrequency;
	float LookAtDistance;
};
