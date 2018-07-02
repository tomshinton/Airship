#pragma once

#include "Engine/DataTable.h"
#include "InventoryFunctions.generated.h"

struct FInventoryItemRow;
struct FInventory;

UCLASS()
class AIRSHIP_API UInventoryFunctions : public UObject
{
	GENERATED_BODY()

public:

	static FInventoryItemRow* GetItemInfo(const int32 ItemID);
	static UDataTable* GetDataTable();

	static void AddItemFromID(FInventory& Inventory, const int32 ItemID, const int32 Quantity);
	static void RemoveItem(FInventory& Inventory, const int32 ItemID, const int32 Quantity);
};

