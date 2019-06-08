#pragma once

#include "InventorySettings.h"
#include "InventoryItemRow.h"
#include "Clip.h"

#include "InventoryItem.generated.h"

class AProjectileBase;

namespace InventoryItemStatics
{
	const FName DefaultItemName = "Item";
}

USTRUCT(BlueprintType)
struct AIRCORE_API FInventoryItem
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

	void Print()
	{
		FString Callback = ItemInfo.IsNullSlot ? "Empty" : ItemInfo.ItemName.ToString();
		UE_LOG(LogTemp, Log, TEXT("%s"), *Callback);
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