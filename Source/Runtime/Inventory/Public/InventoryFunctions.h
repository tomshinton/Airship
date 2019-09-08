#pragma once

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

	static void TransferItems(const FName& InItemID, const int32 InQuantity, CompoundInventory& InInventoryToRemoveFrom, CompoundInventory& InInventoryToAddTo);
	INVENTORY_API static void SwapSlots(const InventorySlotReference& InFirstSlotReference, const InventorySlotReference& InSecondSlotReference);
	static FInventoryItem GetItemBySlotReference(const InventorySlotReference& InReference);
	static void SetItemBySlotReference(const FInventoryItem& InItem, const InventorySlotReference& InReference);

	static bool InventoryContains(const CompoundInventory& InInventory, const FName& InItemID, const int32& InQuantity);
	static int32 GetNumItemsInInventory(const CompoundInventory& InInventory, const FName& ItemID);
	static int32 GetNumStacksInInventory(const CompoundInventory& InInventory, const FName& InItemID);
};

