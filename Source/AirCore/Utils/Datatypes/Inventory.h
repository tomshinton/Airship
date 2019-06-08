#pragma once

#include "InventoryItem.h"

#include "Inventory.generated.h"

USTRUCT(BlueprintType)
struct AIRCORE_API FInventory
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