// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include "MoreManagers/Public/ManagerCore/Manager.h"

#include "TestManager.generated.h"

UCLASS(Blueprintable)
class MOREMANAGERS_API UTestManager : public UManager
{
	GENERATED_BODY()

	UTestManager();

	virtual void Tick() override;

private:
	int32 TickCount;
};