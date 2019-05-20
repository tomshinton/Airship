// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagers/Public/ManagerCore/Manager.h"

UManager::UManager()
	: IsTickEnabled(false)
	, TickFrequency(0.f)
	, ShouldDeferCompleteCallback(false)
	, TickHandle()
	, SetupCompleteCallback(nullptr)
{}

void UManager::Start(const TFunction<void()>& OnSetupCompleteCallback, UWorld* const WorldContext)
{
	CachedWorld = WorldContext;
	SetupCompleteCallback = OnSetupCompleteCallback;

	OnStart();

	if (GetIsTickEnabled())
	{
		BeginTick();
	}

	if (!ShouldDeferCompleteCallback)
	{
		OnSetupCompleteCallback();
	}
}

void UManager::Tick()
{
	if (GetIsTickEnabled())
	{
		GetDeltaTime();
		OnTick(CachedDeltaTime);
	}
}

void UManager::BeginTick()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(TickHandle, this, &UManager::Tick, TickFrequency, true, TickFrequency);
	}
}

void UManager::SetupComplete()
{
	if (SetupCompleteCallback)
	{
		bHasBeganStart = true;
		SetupCompleteCallback();
	}
}

bool UManager::GetIsTickEnabled() const
{
	return !FMath::IsNearlyZero(TickFrequency) && IsTickEnabled;
}

float UManager::GetDeltaTime()
{
	if (CachedWorld)
	{
		const float CurrentGameTime = CachedWorld->GetTimeSeconds();
		const float NewDeltaTime = CurrentGameTime - TimeOfLastTick;

		TimeOfLastTick = CurrentGameTime;
		CachedDeltaTime = NewDeltaTime;

		return NewDeltaTime;
	}

	//if we cant calculate an appropriate DeltaTime, approximate
	return TickFrequency;
}

UWorld* UManager::GetWorld() const
{
	return CachedWorld;
}
