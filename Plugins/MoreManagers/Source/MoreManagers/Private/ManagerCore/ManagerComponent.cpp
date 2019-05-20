// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagers/Public/ManagerCore/ManagerComponent.h"
#include "MoreManagers/Public/ManagerCore/TestManager.h"

#include <Runtime/Core/Public/Misc/AssertionMacros.h>

DEFINE_LOG_CATEGORY(ManagerComponentLog);

UManagerComponent::UManagerComponent()
	: TotalManagersToSpinUp(0)
	, RequestedManagers()
	, ManagerMap()
	, ManagerSpinupCallback(nullptr)
{
	if (!ManagerSpinupCallback)
	{
		ManagerSpinupCallback = [this]() 
		{
			OnManagerSetupComplete();
		};
	}

	RequestedManagers.Emplace(UTestManager::StaticClass());
	RequestedManagers.Emplace(UTestManager::StaticClass());
	RequestedManagers.Emplace(UTestManager::StaticClass());
	RequestedManagers.Emplace(UTestManager::StaticClass());

	TotalManagersToSpinUp = RequestedManagers.Num();
}

void UManagerComponent::OnManagerSetupComplete()
{
	SpinupManager();
}

void UManagerComponent::SpinupManager()
{
	if (RequestedManagers.Num() > 0)
	{
		if (UManager* NewManager = NewObject<UManager>(this, RequestedManagers[0]))
		{
			ManagerMap.Add(RequestedManagers[0], NewManager);
			RequestedManagers.RemoveAt(0);

			NewManager->Start(ManagerSpinupCallback);
		}
	}
	else
	{
		ensureMsgf(ManagerMap.Num() > TotalManagersToSpinUp, TEXT("Span up %i managers, based on MoreManagers Invoke list (%i) - there are duplicate Manager classes in the Invoke List"), ManagerMap.Num(), TotalManagersToSpinUp);
	}
}
