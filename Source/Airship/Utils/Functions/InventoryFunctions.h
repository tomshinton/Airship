#pragma once

#include "Engine/DataTable.h"
#include "InventoryFunctions.generated.h"

struct FInventoryItemRow;
struct FInventoryItem;
struct FInventory;

UCLASS()
class AIRSHIP_API UInventoryFunctions : public UObject
{
	GENERATED_BODY()

public:

	
	static FInventoryItemRow* GetItemInfo(const FName ItemID);
	static UDataTable* GetDataTable();

	static FInventoryItem AddItemFromID(FInventory& Inventory, const FName ItemID, const int32 Quantity);
	static FInventoryItem RemoveItem(FInventory& Inventory, const FName ItemID, const int32 Quantity);
	static void TransferItems(FName ItemID, int32 Quantity, FInventory& OutInventory, FInventory& InInventory);

	static bool InventoryHasEmptySlots(FInventory& Inventory);
	static void Audit(FName ItemID, int32& Stacks, int32& Total, FInventory& InInventory);
};

