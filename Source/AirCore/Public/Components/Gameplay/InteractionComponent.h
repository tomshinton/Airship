// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AirChar.h"
#include "CollisionQueryParams.h"
#include "WorldCollision.h"
#include "InteractionComponent.generated.h"

UCLASS()
class UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UInteractionComponent();

	virtual void BeginPlay() override;

	void StartInteraction();
	void EndInteraction();

private:

	void SetupInput(APawn* InNewPawn);

	void EnableTick();
	void BuildCachedTraceParams();

	void GetLookAtLocations(const FVector2D& InViewportCentre, FVector& TraceStart, FVector& TraceEnd) const;

	bool ShouldTrace() const;

	FTransform GetCurrentOwnerTransform() const;
	void SetLastKnownTransform();

	UFUNCTION()
	void Look();

	UFUNCTION()
	void OnLookOver(const TArray<FHitResult>& InHits);

	UPROPERTY()
	AActor* HoveredActor;

	UPROPERTY()
	AAirChar* CachedOwningPawn;

	bool IsAlreadyProcessingLook;

	FCollisionQueryParams CachedTraceParams;
	FTraceDelegate OnLookOverDelegate;

	UPROPERTY()
	UWorld* CachedWorld;

	float LookAtFrequency;
	float LookAtDistance;

	FTimerHandle LookAtTimerHandle;

	float FlatRefreshTime;
	float CurrentTraceCooldown;
	FTransform LastKnownOwnerTransform;
};
