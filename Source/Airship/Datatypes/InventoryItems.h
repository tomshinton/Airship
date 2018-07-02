#pragma once

#include "Engine/DataTable.h"
#include "Utils/InventoryFunctions.h"
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
		TSubclassOf<AActor> ItemActorClass;

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
		: ItemID(0)
		, Quantity(0)
	{}

	FInventoryItem(const int32 InItemID, const int32 InQuantity)
		: ItemID(InItemID)
		, Quantity(InQuantity)
	{
		ItemInfo = *UInventoryFunctions::GetItemInfo(ItemID);
	}

public:
	int32 ItemID;

	UPROPERTY(VisibleAnywhere)
	int32 Quantity;

	bool IsItemValid()
	{
		return !ItemInfo.IsNullSlot;
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