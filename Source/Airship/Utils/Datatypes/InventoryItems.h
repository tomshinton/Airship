#pragma once

#include "Engine/DataTable.h"
#include "../Functions/InventoryFunctions.h"

#include "InventoryItems.generated.h"

class AProjectileBase;
class AWorldItem;

USTRUCT(Blueprintable, BlueprintType)
struct FClip
{
	GENERATED_BODY()

	explicit FClip()
	: CurrentClip(0)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
	FName AmmoName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
	TSubclassOf<AProjectileBase> AmmoClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
	int32 ClipSize;

	void SetClipCount(const int32 NewClip)
	{
		CurrentClip = FMath::Clamp<int32>(NewClip, 0, ClipSize);
	}

	int32 GetClipCount() const
	{
		return CurrentClip;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
	int32 CurrentClip;
};

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
	bool IsNullSlot;

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
	FClip Clip;
};

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	FInventoryItem()
		: ItemID("Item")
		, Quantity(0)
		, Clip(FClip())
	{}

	FInventoryItem(const FName InItemID, const int32 InQuantity, const FClip InClip)
		: ItemID(InItemID)
		, Quantity(InQuantity)
		, Clip(InClip)
	{
		ItemInfo = *UInventoryFunctions::GetItemInfo(ItemID);
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