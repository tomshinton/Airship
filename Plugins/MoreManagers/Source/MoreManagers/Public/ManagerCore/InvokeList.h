// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/CoreUObject/Public/UObject/SoftObjectPath.h>
#include <Runtime/CoreUObject/Public/UObject/ObjectMacros.h>

#include "InvokeList.generated.h"

class UManager;
class UManagerComponent;

// List of managers to spin up when launching the game
UCLASS(config=Game, defaultconfig)
class MOREMANAGERS_API UInvokeList : public UObject
{
	GENERATED_BODY()

	friend UManagerComponent;

public:

	UInvokeList()
		: InvokeList()
	{
	};

	UPROPERTY(config, EditAnywhere, Category = Managers)
	TArray<TSubclassOf<UManager>> InvokeList;
	
private:

	static UInvokeList* Get()
	{
		return GetMutableDefault<UInvokeList>();
	}

	static TArray<TSubclassOf<UManager>> GetList()
	{
		if (UInvokeList* InvokeList = GetMutableDefault<UInvokeList>())
		{
			return InvokeList->InvokeList;
		}

		return TArray<TSubclassOf<UManager>>();
	}
};