#pragma once

#include "Runtime/Inventory/Public/InventoryFunctions.h"
#include "Runtime/Inventory/Public/InventorySettings.h"
#include "Runtime/Inventory/Public/InventoryTypes/Inventory.h"
#include "Runtime/Inventory/Public/InventoryTypes/InventoryItem.h"

FInventoryItem UInventoryFunctions::AddItemFromID(FInventory& Inventory, const FName ItemID, const int32 Quantity)
{
	FInventoryItemRow* NewItemInfo = UInventorySettings::GetItemInfo(ItemID);

	if (NewItemInfo)
	{
		int32 QuantityLeft = Quantity;

		//Top up existing slots
		for (FInventoryItem& ExistingStack : Inventory.ItemSlots)
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
				for (FInventoryItem& ExistingSlot : Inventory.ItemSlots)
				{
					const int32 NewStackSize = (NewItemInfo->Stacks ? FMath::Clamp(QuantityLeft, 0, NewItemInfo->StackSize) : 1);
					FInventoryItem NewStack = FInventoryItem(ItemID, NewStackSize, NewItemInfo->Clip);
					
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
						return FInventoryItem(ItemID, QuantityLeft, NewItemInfo->Clip);
					}
				}
			}
		}
	}
	//Leftover from add
	return FInventoryItem(ItemID, Quantity, NewItemInfo->Clip);
}

FInventoryItem UInventoryFunctions::RemoveItem(FInventory& InventoryToRemoveFrom, const FName ItemID, const int32 Quantity)
{
	int32 QuantityLeft = Quantity;
	int32 AmountRemoved = 0;

	FInventoryItemRow* NewItemInfo = UInventorySettings::GetItemInfo(ItemID);

	if (NewItemInfo)
	{
		for (int32 i = InventoryToRemoveFrom.ItemSlots.Num() - 1; i >= 0; i--)
		{
			FInventoryItem& CurrInventoryItem = InventoryToRemoveFrom.ItemSlots[i];

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

	return AmountRemoved > 0 ? FInventoryItem(ItemID, AmountRemoved, NewItemInfo->Clip) : FInventoryItem();
}

bool UInventoryFunctions::InventoryHasEmptySlots(FInventory& Inventory)
{
	int32 EmptySlots = 0;

	for (const FInventoryItem& ExistingSlot : Inventory.ItemSlots)
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

	for (FInventoryItem& ExistingSlot : InInventory.ItemSlots)
	{
		if (ExistingSlot.ItemID == ItemID)
		{
			Stacks++;
			Total += ExistingSlot.Quantity;
		}
	}
}

int32 UInventoryFunctions::GetNumStacksInInventory(const FInventory& Inventory, const FName& InItemID)
{
	int32 AmountFound = 0;
	for (const FInventoryItem& Item : Inventory.ItemSlots)
	{
		if (Item.ItemID == InItemID)
		{
			AmountFound++;
		}
	}

	return AmountFound;
}

bool UInventoryFunctions::InventoryContains(const FInventory& InInventory, const FName& InItemID, const int32& InQuantity)
{
	int32 AmountFound = 0;
	for (const FInventoryItem& Item : InInventory.ItemSlots)
	{
		if (Item.ItemID == InItemID)
		{
			AmountFound += Item.Quantity;
		}
	}

	if (AmountFound == InQuantity)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int32 UInventoryFunctions::GetNumItemsInInventory(const FInventory& Inventory, const FName& ItemID)
{
	int32 AmountFound = 0;
	for (const FInventoryItem& Item : Inventory.ItemSlots)
	{
		if (Item.ItemID == ItemID)
		{
			AmountFound += Item.Quantity;
		}
	}
	
	return AmountFound;
}

void UInventoryFunctions::TransferItems(FName ItemID, int32 Quantity, FInventory& InventoryToRemoveFrom, FInventory& InventoryToAddTo)
{
	FInventoryItem RemovedItem = RemoveItem(InventoryToRemoveFrom, ItemID, Quantity);
	if (RemovedItem.Quantity > 0)
	{
		FInventoryItem LeftoverItems = AddItemFromID(InventoryToAddTo, RemovedItem.ItemID, RemovedItem.Quantity);
		if (LeftoverItems.Quantity > 0)
		{
			AddItemFromID(InventoryToRemoveFrom, LeftoverItems.ItemID, LeftoverItems.Quantity);
		}
	}
}

