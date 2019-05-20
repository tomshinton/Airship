// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include "Engine/GameInstance.h"
#include "MM_GameInst.generated.h"

class UManagerComponent;

UCLASS()
class MOREMANAGERS_API UMM_GameInst : public UGameInstance
{
	GENERATED_BODY()

public:
	UMM_GameInst();

	UPROPERTY()
	UManagerComponent* ManagerComponent;

	virtual void StartGameInstance() override;
	virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override;
};
