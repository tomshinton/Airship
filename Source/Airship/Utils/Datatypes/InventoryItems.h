#pragma once

#include "Engine/DataTable.h"
#include "../Functions/InventoryFunctions.h"
#include "WorldItem.h"


#include "InventoryItems.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FInventoryItemRow : public FTableRowBase
{
public:

	GENERATED_BODY()

		FInventoryItemRow()
		: IsNullSlot(true)
		, ItemIcon(nullptr)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		FString ItemNameReadable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		TSubclassOf<AWorldItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		bool Stacks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		int32 StackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		bool IsNullSlot;
};

USTRUCT(BlueprintType)
struct FInventoryItem
{

	GENERATED_BODY()

	FInventoryItem()
		: ItemID("Item")
		, Quantity(0)
	{}

	FInventoryItem(const FName InItemID, const int32 InQuantity)
		: ItemID(InItemID)
		, Quantity(InQuantity)
	{
		ItemInfo = *UInventoryFunctions::GetItemInfo(ItemID);
	}

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FName ItemID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 Quantity;

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

private:

	UPROPERTY(VisibleAnywhere)
	FInventoryItemRow ItemInfo;

	FORCEINLINE bool operator==(const FInventoryItem& Other) const
	{
		return Other.ItemID == ItemID;
	}
};

USTRUCT(BlueprintType)
struct FInventory
{

	GENERATED_BODY()

	FInventory()
		: Inventory()
		, InventorySize(32)
	{}

public:
	UPROPERTY(VisibleAnywhere)
	TArray<FInventoryItem> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	int32 InventorySize;
};