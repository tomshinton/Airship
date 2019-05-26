// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagers/Public/ManagerCore/Manager.h"

UManager::UManager()
	: IsTickEnabled(false)
	, TickFrequency(0.f)
	, ShouldDeferCompleteCallback(false)
	, TickHandle()
	, SetupCompleteCallback(nullptr)
{
	TickFunction = [this]()
	{ 
		Tick();
	};
}

void UManager::Start(const TFunction<void(const UManager*)>& OnSetupCompleteCallback, const TFunction<void(TFunction<void()>)>& DeferTickFunctionHelper, UWorld* const WorldContext)
{
	CachedWorld = WorldContext;
	SetupCompleteCallback = OnSetupCompleteCallback;

	OnStart();

	if (GetIsTickDeferred())
	{
		DeferTickFunctionHelper(TickFunction);
	}
	else if (GetIsTickEnabled())
	{
		BeginTick();
	}

	if (!ShouldDeferCompleteCallback)
	{
		OnSetupCompleteCallback(this);
	}
}

void UManager::Tick()
{
	if (GetIsTickEnabled() || GetIsTickDeferred())
	{
		GetDeltaTime();
		OnTick(CachedDeltaTime);
	}
}

void UManager::BeginTick()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(TickHandle, this, &UManager::Tick, TickFrequency, true, 0.f);
	}
}

void UManager::SetupComplete()
{
	if (SetupCompleteCallback)
	{
		bHasBeganStart = true;
		SetupCompleteCallback(this);
	}
}

bool UManager::GetIsTickEnabled() const
{
	return (!FMath::IsNearlyZero(TickFrequency)) && IsTickEnabled;
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
