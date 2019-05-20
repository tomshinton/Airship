// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include "MoreManagers/Public/ManagerCore/Manager.h"

#include "ManagerComponent.generated.h"

class UMM_GameInst;

DECLARE_LOG_CATEGORY_EXTERN(ManagerComponentLog, Log, All);

UCLASS()
class MOREMANAGERS_API UManagerComponent : public UActorComponent
{
	GENERATED_BODY()

	friend UMM_GameInst;

public:

	UManagerComponent();

protected:

	void OnManagerSetupComplete();
	void SpinupManager();

private:

	int32 TotalManagersToSpinUp;

	TArray<TSubclassOf<UManager>> RequestedManagers;

	UPROPERTY()
	TMap<TSubclassOf<UManager>, UManager*> ManagerMap;

	UPROPERTY()
	UWorld* CachedWorld;

	TFunction<void()> ManagerSpinupCallback;
};
