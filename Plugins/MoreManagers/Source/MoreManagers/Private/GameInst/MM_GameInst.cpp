// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagers/Public/GameInst/MM_GameInst.h"
#include "MoreManagers/Public/ManagerCore/ManagerComponent.h"

namespace MMGameInstPrivate
{
	const FName ManagerComponentName = TEXT("ManagerComponent");
}

UMM_GameInst::UMM_GameInst()
	: ManagerComponent(CreateDefaultSubobject<UManagerComponent>(MMGameInstPrivate::ManagerComponentName))
{
}

void UMM_GameInst::StartGameInstance()
{
	if (ManagerComponent)
	{
		ManagerComponent->SpinupManager();
	}
}

FGameInstancePIEResult UMM_GameInst::StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
{
	Super::StartPlayInEditorGameInstance(LocalPlayer, Params);

	if (ManagerComponent)
	{
		ManagerComponent->SpinupManager();
	}

	return FGameInstancePIEResult::Success();
}
