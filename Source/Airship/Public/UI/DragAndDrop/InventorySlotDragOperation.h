// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventorySlot.h"
#include "InventorySlotDragOperation.generated.h"

/**
 * 
 */
UCLASS()
class AIRSHIP_API UInventorySlotDragOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "IncomingSlot", ExposeOnSpawn = true), Category = "Slot Info")
	UInventorySlot* IncomingSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "IncomingSlot", ExposeOnSpawn = true), Category = "Slot Info")
	UAirInventory* SourceInventory;
};
