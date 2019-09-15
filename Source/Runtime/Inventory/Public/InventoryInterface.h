// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/CoreUObject/Public/UObject/Interface.h>

#include "Runtime/Inventory/Public/InventoryTypes/InventoryBag.h"

#include "InventoryInterface.generated.h"

class CompoundInventory;
struct FInventoryItem;

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_MULTICAST_DELEGATE(FOnInventoryInitialised);
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
	virtual FOnInventoryInitialised& GetOnInventoryInitialised() = 0;

	virtual int32 GetCurrentFocusedSlot() const = 0;
		
	virtual CompoundInventory* GetInventory() = 0;

	virtual FInventoryItem GetItemBySlot(const FGuid& InBagID, const int32 InInventorySlot) const = 0;

	virtual const FInventoryBag* GetBagByType(const EBagType& InBagType) const = 0;
	virtual const FInventoryBag* GetBagByID(const FGuid& InBagID) const = 0;
	virtual FGuid GetBagIDByIndex(const int32 InIndex) const = 0;
	virtual FGuid GetFirstPrimaryBagID() const = 0;
};
