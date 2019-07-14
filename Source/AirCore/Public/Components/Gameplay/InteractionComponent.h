// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractionInterface.h"
#include "InteractionComponent.generated.h"

class AAirChar;
class UActorComponent;

USTRUCT()
struct FViewTargetInfo
{
public:

	GENERATED_BODY()

	FViewTargetInfo()
	: ViewStart(FVector::ZeroVector)
	, Rotation(FRotator::ZeroRotator)
	, ViewDistance(0.f)
	{}

	FViewTargetInfo(const float InViewDistance)
	: ViewStart(FVector::ZeroVector)
	, Rotation(FRotator::ZeroRotator)
	, ViewDistance(InViewDistance)
	{}

	void Set(const FVector& InViewStart, const FRotator& InRotation)
	{
		ViewStart = InViewStart;
		Rotation = InRotation;

		if (ViewDistance > 0.f)
		{
			ViewEnd = ViewStart + (Rotation.Vector() * ViewDistance);
		}
	}

	FVector ViewStart;
	FVector ViewEnd;

private:

	FRotator Rotation;
	float ViewDistance;
};

UCLASS(MinimalAPI)
class UInteractionComponent : public UActorComponent
	, public IInteractionInterface
{
	GENERATED_BODY()

public:

	UInteractionComponent();

	virtual void BeginPlay() override;

	void StartInteraction();
	void EndInteraction();

#if WITH_DEV_AUTOMATION_TESTS
	AIRCORE_API UWorld* GetCachedWorld() const { return CachedWorld; };
	AIRCORE_API FCollisionQueryParams& GetCachedTraceParams() { return CachedTraceParams; };
	AIRCORE_API FTraceDelegate& GetOnLookOverDelegate() { return OnLookOverDelegate; };
	AIRCORE_API FTimerHandle& GetTickTimerHandle() { return LookAtTimerHandle; };

	AIRCORE_API void ForceLook() { Look(); };

	AIRCORE_API bool GetIsAlreadyProcessingLook() const { return IsAlreadyProcessingLook; };
	AIRCORE_API TOptional<FTransform> GetLastKnownTransform() { return LastKnownOwnerTransform; };
	AIRCORE_API float GetLookAtFrequency() const { return LookAtFrequency; };
#endif //WITH_DEV_AUTOMATION_TESTS

private:

	//InteractionInterface
	virtual FOnNewItemHovered& GetOnNewItemHoveredDelegate() override;;
	//~InteractionInterface

	void SetupInput(APawn* InNewPawn);

	void EnableTick();
	void BuildCachedTraceParams();

	void GetCurrentViewTargetInfo(FViewTargetInfo& OutLookAtInfo) const;

	bool ShouldTrace() const;

	FTransform GetCurrentOwnerTransform() const;
	void SetLastKnownTransform();

	UFUNCTION()
	void Look();

	UFUNCTION()
	void OnLookOver(const TArray<FHitResult>& InHits);

	void ResetHoveredInteractable();

	TScriptInterface<IInteractableInterface> HoveredInteractable;

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
	TOptional<FTransform> LastKnownOwnerTransform;

	FOnNewItemHovered OnNewItemHovered;
};
