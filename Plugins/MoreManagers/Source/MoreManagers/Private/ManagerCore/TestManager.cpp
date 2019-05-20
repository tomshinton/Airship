// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagers/Public/ManagerCore/TestManager.h"

UTestManager::UTestManager()
{
	IsTickEnabled = true;
	TickFrequency = 1.f;

	ShouldDeferCompleteCallback = false;
}

void UTestManager::Tick()
{
	if (GEngine)
	{
		TickCount++;
		const FString TickTypeString = ShouldDeferCompleteCallback ? TEXT("Deferred") : TEXT("Standard");

		GEngine->AddOnScreenDebugMessage(1, 1, FColor::White, FString::Printf(TEXT("TickType: %s"), *TickTypeString));
		GEngine->AddOnScreenDebugMessage(2, 1, FColor::White, FString::Printf(TEXT("TickCount: %i, DynamicDeltaTime: %f"), TickCount, CachedDeltaTime));
	}

	Super::Tick();
}
