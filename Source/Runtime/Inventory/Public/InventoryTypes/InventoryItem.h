// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/Inventory/Public/InventorySettings.h"
#include "Runtime/Inventory/Public/InventoryTypes/Clip.h"
#include "Runtime/Inventory/Public/InventoryTypes/InventoryItemRow.h"

#include "InventoryItem.generated.h"

class AProjectileBase;

namespace InventoryItemStatics
{
	const FName DefaultItemName = "Item";
}

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	FInventoryItem()
		: ItemID(InventoryItemStatics::DefaultItemName)
		, Quantity(0)
		, Clip(FClip())
	{}

	FInventoryItem(const FName InItemID, const int32 InQuantity, const FClip InClip)
		: ItemID(InItemID)
		, Quantity(InQuantity)
		, Clip(InClip)
	{
		ItemInfo = *UInventorySettings::GetItemInfo(ItemID);
	}

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FName ItemID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 Quantity;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FClip Clip;
	
	bool IsItemValid()
	{
		return ItemInfo.IsNullSlot;
	}

	TSubclassOf<AWorldItem> GetItemClass()
	{
		return ItemInfo.ItemClass;
	}

	FClip& GetItemClip() 
	{
		return Clip;
	}

private:

	UPROPERTY(VisibleAnywhere)
	FInventoryItemRow ItemInfo;

	FORCEINLINE bool operator==(const FInventoryItem& Other) const
	{
		return Other.ItemID == ItemID;
	}
};