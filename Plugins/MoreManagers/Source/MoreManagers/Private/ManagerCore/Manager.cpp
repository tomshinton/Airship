// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagers/Public/ManagerCore/Manager.h"

UManager::UManager()
	: SetupCompleteCallback(nullptr)
	, ShouldDeferCompleteCallback(false)
	, IsTickEnabled(false)
	, TickFrequency(0.f)
{

}

void UManager::Start(const TFunction<void()>& OnSetupCompleteCallback)
{
	SetupCompleteCallback = OnSetupCompleteCallback;

	OnStart();

	if (!ShouldDeferCompleteCallback)
	{
		OnSetupCompleteCallback();
	}
}

void UManager::Tick()
{
	if (GetIsTickEnabled())
	{
		OnTick(TickFrequency);
	}
}

void UManager::SetupComplete()
{
	if (SetupCompleteCallback)
	{
		SetupCompleteCallback();
	}
}

bool UManager::GetIsTickEnabled() const
{
	return !FMath::IsNearlyZero(TickFrequency) && IsTickEnabled;
}
