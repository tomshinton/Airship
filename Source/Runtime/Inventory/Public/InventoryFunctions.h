#pragma once

#include "Engine/DataTable.h"
#include "InventoryFunctions.generated.h"

struct FInventoryItemRow;
struct FInventoryItem;
struct FInventory;

UCLASS(MinimalAPI)
class UInventoryFunctions : public UObject
{
	GENERATED_BODY()

public:

	static FInventoryItem AddItemFromID(FInventory& Inventory, const FName ItemID, const int32 Quantity);
	static FInventoryItem RemoveItem(FInventory& InventoryToRemoveFrom, const FName ItemID, const int32 Quantity);
	static void TransferItems(FName ItemID, int32 Quantity, FInventory& InventoryToRemoveFrom, FInventory& InventoryToAddTo);

	static bool InventoryHasEmptySlots(FInventory& Inventory);
	static void Audit(FName ItemID, int32& Stacks, int32& Total, FInventory& InInventory);
	
	static bool InventoryContains(const FInventory& Inventory, const FName& InItemID, const int32& InQuantity);
	static int32 GetNumItemsInInventory(const FInventory& Inventory, const FName& ItemID);
	static int32 GetNumStacksInInventory(const FInventory& Inventory, const FName& InItemID);
};

