// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include "MoreManagers/Public/ManagerCore/Manager.h"

#include "ManagerComponent.generated.h"

class AMM_GameState;

DECLARE_LOG_CATEGORY_EXTERN(ManagerComponentLog, Log, All);

UCLASS()
class MOREMANAGERS_API UManagerComponent : public UActorComponent
{
	GENERATED_BODY()

	friend AMM_GameState;

public:

	UManagerComponent();

protected:

	void OnManagerSetupComplete(const UManager* FinishedClass);
	void SpinupManager();

	void SetCachedWorld(UWorld* InCachedWorld) { CachedWorld = InCachedWorld; };

private:

	int32 TotalManagersToSpinUp;

	TArray<TSubclassOf<UManager>> RequestedManagers;

	UPROPERTY()
	TMap<TSubclassOf<UManager>, UManager*> ManagerMap;

	TArray<TFunction<void()>> DeferredTickFunctions;
	TFunction<void(TFunction<void()>)> DeferTickFunctionHelper;

	FTimerHandle DeferredTickHandle;

	float DeferredTickFrequency;
	int32 CurrManagerIndex;

	UPROPERTY()
	UWorld* CachedWorld;

	TFunction<void(const UManager*)> ManagerSpinupCallback;

	bool GetIsManagerSpanUp(const UManager* FinishedManager) const;
	void EmplaceManager(const UManager* FinishedManager);

	void PushTickFunctionOntoStack(const TFunction<void()>& InTickFunction);

	void DeferredTick();
};
