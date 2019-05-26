// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

//#include "CoreMinimal.h"
#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/CoreUObject/Public/UObject/SoftObjectPath.h>
#include <Runtime/CoreUObject/Public/UObject/ObjectMacros.h>

#include "InvokeList.generated.h"

// List of managers to spin up when launching the game
UCLASS(config=Game)
class MOREMANAGERS_API UInvokeList : public UObject
{
	GENERATED_BODY()

public:

	UInvokeList()
		: InvokeList()
	{
	};

	UPROPERTY(config, EditAnywhere, Category = Managers)
	TArray<FStringAssetReference> InvokeList;
};