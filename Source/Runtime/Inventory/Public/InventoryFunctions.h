#pragma once

#include <Runtime/Engine/Classes/Engine/DataTable.h>

class CompoundInventory;

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
	
	static bool InventoryContains(const CompoundInventory& InInventory, const FName& InItemID, const int32& InQuantity);
	static int32 GetNumItemsInInventory(const CompoundInventory& InInventory, const FName& ItemID);
	static int32 GetNumStacksInInventory(const CompoundInventory& InInventory, const FName& InItemID);
};

