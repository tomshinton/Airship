// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/CoreUObject/Public/UObject/Interface.h>

#include "InventoryInterface.generated.h"

struct FInventory;
struct FInventoryItem;

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSlotFocusUpdated, const int32);

UINTERFACE(BlueprintType, MinimalAPI)
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

class INVENTORY_API IInventoryInterface
{
	GENERATED_BODY()

public:

	virtual FOnInventoryUpdated& GetOnInventoryUpdated() = 0;
	virtual FOnSlotFocusUpdated& GetOnSlotFocusUpdated() = 0;

	virtual FInventory& GetInventory() = 0;

	virtual FInventoryItem GetItemBySlot(const int32 InSlot) const = 0;
	virtual void SetItemBySlot(const FInventoryItem& InItem, const int32 InSlot) = 0;

	virtual int32 GetCurrentFocusedSlot() const = 0;
};
