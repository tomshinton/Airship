#include "InventoryFunctions.h"
#include "Datatypes/InventoryItems.h"
#include "ConstructorHelpers.h"

FInventoryItemRow* UInventoryFunctions::GetItemInfo(int32 ItemID)
{
	FInventoryItemRow* NewRow = nullptr;
	UDataTable* ItemDataTable = GetDataTable();
	if (ItemDataTable)
	{
		int32 NumRows = ItemDataTable->GetRowNames().Num();
		if (ItemID <= (NumRows - 1))
		{
			const FName RowName = FName(*FString::FromInt(ItemID));
			FString Context;
			NewRow = ItemDataTable->FindRow<FInventoryItemRow>(RowName, Context, false);
		}
	}

	return NewRow;
}

UDataTable* UInventoryFunctions::GetDataTable()
{
	const FString AnimClassStringTest = "DataTable'/Game/Data/DataTables/ItemData.ItemData'";
	UDataTable* Table = LoadObject<UDataTable>(NULL, *AnimClassStringTest);
	return Table;
}

void UInventoryFunctions::AddItemFromID(FInventory& Inventory, const int32 ItemID, const int32 Quantity)
{
	if (FInventoryItemRow* NewItemInfo = GetItemInfo(ItemID))
	{
		int32 QuantityLeft = Quantity;

		//Do we have room to add?
		if (Inventory.Inventory.Num() - 1 > Inventory.InventorySize)
		{
			return;
		}

		if (NewItemInfo->Stacks)
		{
			const int32 StackSize = NewItemInfo->StackSize;

			for (FInventoryItem& ExistingStack : Inventory.Inventory)
			{
				if (ExistingStack.ItemID == ItemID && ExistingStack.Quantity < StackSize)
				{
					const int32 AmountToAddToStack = FMath::Clamp(Quantity, 0, StackSize - ExistingStack.Quantity);
					ExistingStack.Quantity += AmountToAddToStack;
					QuantityLeft -= AmountToAddToStack;
				}
			}

			if (QuantityLeft > 0)
			{
				int32 StacksToMake = NewItemInfo->Stacks ? FMath::CeilToInt((float)QuantityLeft / (float)StackSize) : 1;

				for (int32 i = 0; i < StacksToMake; i++)
				{
					FInventoryItem NewStack = FInventoryItem(ItemID, FMath::Clamp(QuantityLeft, 0, StackSize));
					Inventory.Inventory.Add(NewStack);
					QuantityLeft -= StackSize;
				}
			}
		}
		else
		{
			for (int32 i = 0; i < Quantity; i++)
			{
				FInventoryItem NewStack = FInventoryItem(ItemID, 1);
				Inventory.Inventory.Add(NewStack);
			}
		}
	}
}

void UInventoryFunctions::RemoveItem(FInventory& Inventory, const int32 ItemID, const int32 Quantity)
{
	int32 QuantityLeft = Quantity;

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
					Inventory.Inventory.RemoveAt(i);
				}

				QuantityLeft -= AmountToRemove;
			}
		}
	}
}
