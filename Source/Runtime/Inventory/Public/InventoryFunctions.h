// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/Inventory/Public/InventoryTypes/InventoryBag.h"

class CompoundInventory;
class InventorySlotReference;

struct FInventoryItemRow;
struct FInventoryItem;

enum class EOperationReturnType
{
	BagFull,
	BagEmpty,
	AllItemsAdded,
	AllItemsRemoved,
	InvalidBag
};

class InventoryFunctions
{
public:
	static bool AddItemFromID(CompoundInventory& InInventory, const FName& InItemID, const int32 InQuantity);
	static EOperationReturnType AddItemToBag(const CompoundInventory& InInventory, const FGuid& InBagID, const FInventoryItemRow& InNewItemInfo, int32& InQuantityLeft);

	static bool RemoveItemFromID(CompoundInventory& Inventory, const FName& ItemID, const int32 Quantity);
	static EOperationReturnType RemoveItemFromBag(const CompoundInventory& InInventory, const FGuid& InBagID, const FName& InItemID, int32& InQuantityLeft);

	INVENTORY_API static void SwapSlots(const InventorySlotReference& InFirstSlotReference, const InventorySlotReference& InSecondSlotReference);
	static FInventoryItem GetItemBySlotReference(const InventorySlotReference& InReference);
	static void SetItemBySlotReference(const FInventoryItem& InItem, const InventorySlotReference& InReference);

	static bool InventoryContains(const CompoundInventory& InInventory, const FName& InItemID, const int32& InQuantity);
	static int32 GetNumItemsInInventory(const CompoundInventory& InInventory, const FName& ItemID);
	static int32 GetNumStacksInInventory(const CompoundInventory& InInventory, const FName& InItemID);

	INVENTORY_API static TOptional<InventorySlotReference> GetFirstSlotOfType(const CompoundInventory& InInventory, const EBagType& InSlotDomain);
	INVENTORY_API static TOptional<InventorySlotReference> GetFirstSlotNotOfType(const CompoundInventory& InInventory, const EBagType& InSlotDomain);

	static TOptional<InventorySlotReference> GetFirstEmptySlotInBag(const CompoundInventory& InInventory, const FGuid& InBagID);
	
private:

	static TOptional<InventorySlotReference> GetFirstSlotByType(const CompoundInventory& InInventory, const EBagType& InBagType, const bool ShouldExcludeType = false);
};

