// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AirChar.h"
#include "CollisionQueryParams.h"
#include "WorldCollision.h"
#include "InteractionComponent.generated.h"

UCLASS(MinimalAPI)
class UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UInteractionComponent();

	virtual void BeginPlay() override;

	void StartInteraction();
	void EndInteraction();

	AActor* GetHoveredActor() const { return HoveredActor; };

#if WITH_DEV_AUTOMATION_TESTS
	AIRCORE_API UWorld* GetCachedWorld() const { return CachedWorld; };
	AIRCORE_API FCollisionQueryParams& GetCachedTraceParams() { return CachedTraceParams; };
	AIRCORE_API FTraceDelegate& GetOnLookOverDelegate() { return OnLookOverDelegate; };
	AIRCORE_API FTimerHandle& GetTickTimerHandle() { return LookAtTimerHandle; };

	AIRCORE_API void ForceLook() { Look(); };

	AIRCORE_API bool GetIsAlreadyProcessingLook() const { return IsAlreadyProcessingLook; };

#endif //WITH_DEV_AUTOMATION_TESTS

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
