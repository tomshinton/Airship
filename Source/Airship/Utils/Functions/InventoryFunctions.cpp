#include "InventoryFunctions.h"
#include "../Datatypes/InventoryItems.h"
#include "ConstructorHelpers.h"

FInventoryItemRow* UInventoryFunctions::GetItemInfo(FName ItemID)
{
	FInventoryItemRow NewRow;
	FInventoryItemRow* NewRowPtr = &NewRow;
	UDataTable* ItemDataTable = GetDataTable();
	if (ItemDataTable)
	{
		int32 NumRows = ItemDataTable->GetRowNames().Num();
		FString Context;

		NewRowPtr = ItemDataTable->FindRow<FInventoryItemRow>(ItemID, Context, false);
	}

	return NewRowPtr;
}

UDataTable* UInventoryFunctions::GetDataTable()
{
	const FString ItemInfoDataTable = "DataTable'/Game/Data/DataTables/ItemData.ItemData'";
	UDataTable* Table = LoadObject<UDataTable>(NULL, *ItemInfoDataTable);
	return Table;
}

FInventoryItem UInventoryFunctions::AddItemFromID(FInventory& Inventory, const FName ItemID, const int32 Quantity)
{
	if (FInventoryItemRow* NewItemInfo = GetItemInfo(ItemID))
	{
		int32 QuantityLeft = Quantity;

		//Top up existing slots
		for (FInventoryItem& ExistingStack : Inventory.Inventory)
		{
			if (ExistingStack.ItemID == ItemID && (NewItemInfo->Stacks ? ExistingStack.Quantity < NewItemInfo->StackSize : false))
			{
				//There's room in this stack - top it up
				int32 AmountToAdd = FMath::Clamp(NewItemInfo->StackSize - ExistingStack.Quantity, 0, QuantityLeft);
				ExistingStack.Quantity += AmountToAdd;
				QuantityLeft -= AmountToAdd;
			}

			if (QuantityLeft <= 0)
			{
				return FInventoryItem();
			}
		}

		//Create new stacks
		if (QuantityLeft > 0)
		{
			int32 StacksToMake = NewItemInfo->Stacks ? FMath::CeilToInt((float)QuantityLeft / (float)NewItemInfo->StackSize) : QuantityLeft;

			for (int32 i = 0; i < StacksToMake; i++)
			{
				FInventoryItem NewStack = FInventoryItem(ItemID, (NewItemInfo->Stacks ? FMath::Clamp(QuantityLeft, 0, NewItemInfo->StackSize) : 1));

				for (FInventoryItem& ExistingSlot : Inventory.Inventory)
				{
					if (ExistingSlot.ItemID == "Item")
					{
						//this is an empty slot - fill it
						ExistingSlot = NewStack;
						QuantityLeft -= NewStack.Quantity;
					}

					if (QuantityLeft <= 0)
					{
						return FInventoryItem();
					}

					if (!InventoryHasEmptySlots(Inventory))
					{
						return FInventoryItem(ItemID, QuantityLeft);
					}
				}
			}
		}
	}
	//Leftover from add
	return FInventoryItem(ItemID, Quantity);
}

FInventoryItem UInventoryFunctions::RemoveItem(FInventory& Inventory, const FName ItemID, const int32 Quantity)
{
	int32 QuantityLeft = Quantity;
	int32 AmountRemoved = 0;

	if (FInventoryItemRow* NewItemInfo = GetItemInfo(ItemID))
	{
		for (int32 i = Inventory.Inventory.Num() - 1; i >= 0; i--)
		{
			FInventoryItem& CurrInventoryItem = Inventory.Inventory[i];

			if (CurrInventoryItem.ItemID == ItemID && QuantityLeft > 0)
			{
				const int32 AmountToRemove = FMath::Clamp(QuantityLeft, 0, CurrInventoryItem.Quantity);
				CurrInventoryItem.Quantity -= AmountToRemove;
				if (CurrInventoryItem.Quantity <= 0)
				{
					CurrInventoryItem = FInventoryItem();
				}

				QuantityLeft -= AmountToRemove;
				AmountRemoved += AmountToRemove;
			}
		}
	}

	return AmountRemoved > 0 ? FInventoryItem(ItemID, AmountRemoved) : FInventoryItem();
}

bool UInventoryFunctions::InventoryHasEmptySlots(FInventory& Inventory)
{
	int32 EmptySlots = 0;

	for (const FInventoryItem& ExistingSlot : Inventory.Inventory)
	{
		if (ExistingSlot.ItemID == "Item")
		{
			EmptySlots++;
		}
	}

	return EmptySlots > 0 ? true : false;

}

void UInventoryFunctions::Audit(FName ItemID, int32& Stacks, int32& Total, FInventory& InInventory)
{
	Total = 0;
	Stacks = 0;

	for (FInventoryItem& ExistingSlot : InInventory.Inventory)
	{
		if (ExistingSlot.ItemID == ItemID)
		{
			Stacks++;
			Total += ExistingSlot.Quantity;
		}
	}
}

void UInventoryFunctions::TransferItems(FName ItemID, int32 Quantity, FInventory& OutInventory, FInventory& InInventory)
{
	FInventoryItem RemovedItem = RemoveItem(OutInventory, ItemID, Quantity);
	if (RemovedItem.Quantity > 0)
	{
		FInventoryItem LeftoverItems = AddItemFromID(InInventory, RemovedItem.ItemID, RemovedItem.Quantity);
		if (LeftoverItems.Quantity > 0)
		{
			AddItemFromID(OutInventory, LeftoverItems.ItemID, LeftoverItems.Quantity);
		}
	}
}

