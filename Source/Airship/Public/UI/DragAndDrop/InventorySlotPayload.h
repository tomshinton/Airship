// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventorySlotPayload.generated.h"

class UInventorySlot;

UCLASS()
class AIRSHIP_API UInventorySlotPayload : public UObject
{
	GENERATED_BODY()

public:

	UInventorySlot* SourceInventorySlot;	
};
