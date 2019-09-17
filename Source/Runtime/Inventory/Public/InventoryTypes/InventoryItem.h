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
		, BagID(FGuid())
		, SlotID(FGuid::NewGuid())
	{}

	FInventoryItem(const FGuid& InBagID)
		: ItemID(InventoryItemStatics::DefaultItemName)
		, Quantity(0)
		, Clip(FClip())
		, BagID(InBagID)
		, SlotID(FGuid::NewGuid())
	{}

	FInventoryItem(const FName& InItemID, const int32 InQuantity, const FClip& InClip, const FGuid& InBagID)
		: ItemID(InItemID)
		, Quantity(InQuantity)
		, Clip(InClip)
		, BagID(InBagID)
		, SlotID(FGuid::NewGuid())
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
	
	FGuid BagID;

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

	const FGuid& GetSlotID() const
	{
		return SlotID;
	}

private:

	UPROPERTY(VisibleAnywhere)
	FInventoryItemRow ItemInfo;

	FORCEINLINE bool operator==(const FInventoryItem& Other) const
	{
		return Other.ItemID == ItemID;
	}

	FGuid SlotID;
};