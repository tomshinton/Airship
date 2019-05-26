// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagers/Public/ManagerCore/InvokeList.h"
#include "MoreManagers/Public/ManagerCore/ManagerComponent.h"

#include <Runtime/Core/Public/Misc/AssertionMacros.h>

DEFINE_LOG_CATEGORY(ManagerComponentLog);

UManagerComponent::UManagerComponent()
	: TotalManagersToSpinUp(0)
	, RequestedManagers()
	, ManagerMap()
	, DeferredTickFrequency(1.f / 30.f) //approximate 30fps
	, ManagerSpinupCallback(nullptr)
{
	if (!ManagerSpinupCallback)
	{
		ManagerSpinupCallback = [this](const UManager* FinishedManager)
		{
			OnManagerSetupComplete(FinishedManager);
		};
	}

	RequestedManagers = UInvokeList::GetList();
	TotalManagersToSpinUp = RequestedManagers.Num();

	DeferTickFunctionHelper = [this](const TFunction<void()>& TickFunction)
	{
		PushTickFunctionOntoStack(TickFunction);
	};
}

void UManagerComponent::OnManagerSetupComplete(const UManager* FinishedManager)
{
	if (GetIsManagerSpanUp(FinishedManager))
	{
		UE_LOG(ManagerComponentLog, Error, TEXT("%s has already been spanup! DeferCallback likely set to false"), *FinishedManager->GetName());
	}
	else
	{
		EmplaceManager(FinishedManager);
	}

	SpinupManager();
}

void UManagerComponent::SpinupManager()
{
	if (RequestedManagers.Num() > 0)
	{
		if (UManager* NewManager = NewObject<UManager>(this, RequestedManagers[0]))
		{
			ManagerMap.Add(RequestedManagers[0], nullptr);
			RequestedManagers.RemoveAt(0);

			NewManager->Start(ManagerSpinupCallback, DeferTickFunctionHelper, CachedWorld);
		}
	}
	else
	{
		UE_LOG(ManagerComponentLog, Log, TEXT("Span up %i managers, based on MoreManagers Invoke list (%i)"), ManagerMap.Num(), TotalManagersToSpinUp);
	}
}

bool UManagerComponent::GetIsManagerSpanUp(const UManager* FinishedManager) const
{
	for (const TPair<TSubclassOf<UManager>, UManager*>& Manager : ManagerMap)
	{
		if (Manager.Value == FinishedManager)
		{
			return true;
		}
	}

	return false;
}

void UManagerComponent::EmplaceManager(const UManager* FinishedManager)
{
	if (FinishedManager)
	{
		for (const TPair<TSubclassOf<UManager>, UManager*>& Manager : ManagerMap)
		{
			if (FinishedManager->IsA(Manager.Key))
			{
				ManagerMap[Manager.Key] = const_cast<UManager*>(FinishedManager);
				UE_LOG(ManagerComponentLog, Log, TEXT("%s Emplaced in ManagerMap as key %s"), *FinishedManager->GetName(), *Manager.Key->GetName());
			}
		}
	}
}

void UManagerComponent::PushTickFunctionOntoStack(const TFunction<void()>& InTickFunction)
{
	DeferredTickFunctions.Add(InTickFunction);

	if (!DeferredTickHandle.IsValid())
	{
		if (CachedWorld)
		{
			CachedWorld->GetTimerManager().SetTimer(DeferredTickHandle, this, &UManagerComponent::DeferredTick, DeferredTickFrequency, true, 0.f);
		}
	}
}

void UManagerComponent::DeferredTick()
{
	if(DeferredTickFunctions.IsValidIndex(CurrManagerIndex))
	{
		DeferredTickFunctions[CurrManagerIndex]();
		CurrManagerIndex++;

		if (CurrManagerIndex > DeferredTickFunctions.Num() - 1)
		{
			CurrManagerIndex = 0;
		}
	}
}
