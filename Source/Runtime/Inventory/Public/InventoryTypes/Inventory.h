#pragma once

#include "Runtime/Inventory/Public/InventoryTypes/InventoryItem.h"

#include "Inventory.generated.h"

USTRUCT(BlueprintType)
struct FInventory
{
	GENERATED_BODY()

	FInventory()
		: ItemSlots(TArray<FInventoryItem>())
		, InventorySize(32)
	{}

public:
	UPROPERTY(VisibleAnywhere)
	TArray<FInventoryItem> ItemSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemSlots)
	int32 InventorySize;
};