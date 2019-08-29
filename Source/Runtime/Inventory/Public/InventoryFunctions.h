#pragma once

#include <Runtime/Engine/Classes/Engine/DataTable.h>

class CompoundInventory;

struct FInventoryItemRow;
struct FInventoryItem;

class InventoryFunctions
{
public:

	static FInventoryItem AddItemFromID(CompoundInventory& Inventory, const FName ItemID, const int32 Quantity);
	static FInventoryItem RemoveItem(CompoundInventory& InventoryToRemoveFrom, const FName ItemID, const int32 Quantity);
	static void TransferItems(FName ItemID, int32 Quantity, CompoundInventory& InventoryToRemoveFrom, CompoundInventory& InventoryToAddTo);

	static bool InventoryHasEmptySlots(CompoundInventory& Inventory);
	
	static bool InventoryContains(const CompoundInventory& Inventory, const FName& InItemID, const int32& InQuantity);
	static int32 GetNumItemsInInventory(const CompoundInventory& Inventory, const FName& ItemID);
	static int32 GetNumStacksInInventory(const CompoundInventory& Inventory, const FName& InItemID);
};

