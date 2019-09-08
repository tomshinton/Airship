#pragma once

#include "Runtime/Inventory/Public/InventoryFunctions.h"
#include "Runtime/Inventory/Public/InventorySettings.h"
#include "Runtime/Inventory/Public/InventoryTypes/CompoundInventory.h"
#include "Runtime/Inventory/Public/InventoryTypes/InventoryBag.h"
#include "Runtime/Inventory/Public/InventoryTypes/InventoryItem.h"
#include "Runtime/Inventory/Public/InventoryTypes/InventorySlotReference.h"

bool InventoryFunctions::AddItemFromID(CompoundInventory& InInventory, const FName& InItemID, const int32 InQuantity)
{
	if (FInventoryItemRow* NewItemInfo = UInventorySettings::GetItemInfo(InItemID))
	{
		int32 QuantityLeft = InQuantity;

		for (const FInventoryBag& Bag : InInventory.GetAllBags())
		{
			const EOperationReturnType ReturnType = AddItemToBag(InInventory, Bag.GetBagID(), *NewItemInfo, QuantityLeft);

			if (ReturnType == EOperationReturnType::AllItemsAdded)
			{
				return true;
			}
		}
	}

	if (InQuantity > 0)
	{
		return false;
	}

	return true;
}

EOperationReturnType InventoryFunctions::AddItemToBag(const CompoundInventory& InInventory, const FGuid& InBagID, const FInventoryItemRow& InNewItemInfo, int32& InQuantityLeft)
{
	if (FInventoryBag* Bag = InInventory.GetBag(InBagID))
	{
		//Top up existing slots
		for (FInventoryItem& ExistingStack : Bag->BagSlots)
		{
			if (ExistingStack.ItemID == InNewItemInfo.ItemName && (InNewItemInfo.Stacks ? ExistingStack.Quantity < InNewItemInfo.StackSize : false))
			{
				//There's room in this stack - top it up
				int32 AmountToAdd = FMath::Clamp(InNewItemInfo.StackSize - ExistingStack.Quantity, 0, InQuantityLeft);
				ExistingStack.Quantity += AmountToAdd;
				InQuantityLeft -= AmountToAdd;
			}

			if (InQuantityLeft <= 0)
			{
				return EOperationReturnType::AllItemsAdded;
			}
		}

		//Create new stacks
		if (InQuantityLeft > 0)
		{
			const int32 StacksToMake = InNewItemInfo.Stacks ? FMath::CeilToInt((float)InQuantityLeft / (float)InNewItemInfo.StackSize) : InQuantityLeft;

			for (int32 i = 0; i < StacksToMake; ++i)
			{
				for (FInventoryItem& ExistingSlot : Bag->BagSlots)
				{
					const int32 NewStackSize = (InNewItemInfo.Stacks ? FMath::Clamp(InQuantityLeft, 0, InNewItemInfo.StackSize) : 1);
					const FInventoryItem NewStack = FInventoryItem(InNewItemInfo.ItemName, NewStackSize, InNewItemInfo.Clip, InBagID);
					
					if (ExistingSlot.ItemID == "Item")
					{

						ExistingSlot = NewStack;
						InQuantityLeft -= NewStack.Quantity;
					}

					if (InQuantityLeft <= 0)
					{
						return EOperationReturnType::AllItemsAdded;
					}
				}
			}
		}
	}
	else
	{
		return EOperationReturnType::InvalidBag;
	}

	return EOperationReturnType::BagFull;
}

bool InventoryFunctions::RemoveItemFromID(CompoundInventory& InInventory, const FName& InItemID, const int32 InQuantity)
{
	//Backwards so we address non-hotbar related bags first
	int32 QuantityLeft = InQuantity;

	for(int32 i = InInventory.GetAllBags().Num() - 1; i >= 0; i--)
	{
		const FInventoryBag& Bag = InInventory.GetAllBags()[i];
		const EOperationReturnType ReturnType = RemoveItemFromBag(InInventory, Bag.GetBagID(), InItemID, QuantityLeft);

		if (ReturnType == EOperationReturnType::AllItemsRemoved)
		{
			return true;
		}
	}

	return false;
}

EOperationReturnType InventoryFunctions::RemoveItemFromBag(const CompoundInventory& InInventory, const FGuid& InBagID, const FName& InItemID, int32& InQuantityLeft)
{
	if (FInventoryBag* Bag = InInventory.GetBag(InBagID))
	{
		//Remove from existing slots backwards - forwards look odd
		for (int32 i = Bag->BagSlots.Num() - 1; i >= 0; i--)
		{
			FInventoryItem& ExistingStack = Bag->BagSlots[i];

			if (ExistingStack.ItemID == InItemID && InQuantityLeft > 0)
			{
				const int32 AmountToRemove = FMath::Min(ExistingStack.Quantity, InQuantityLeft);

				ExistingStack.Quantity -= AmountToRemove;
				InQuantityLeft -= AmountToRemove;

				if (ExistingStack.Quantity == 0)
				{
					ExistingStack = FInventoryItem();
				}

				if (InQuantityLeft <= 0)
				{
					return EOperationReturnType::AllItemsRemoved;
				}
			}
		}

		if (InQuantityLeft > 0)
		{
			return EOperationReturnType::BagEmpty;
		}
	}

	return EOperationReturnType::InvalidBag;
}



void InventoryFunctions::TransferItems(const FName& InItemID, const int32 InQuantity, CompoundInventory& InInventoryToRemoveFrom, CompoundInventory& InInventoryToAddTo)
{

}

void InventoryFunctions::SwapSlots(const InventorySlotReference& InFirstSlotReference, const InventorySlotReference& InSecondSlotReference)
{
	FInventoryItem FirstSlotItem = GetItemBySlotReference(InFirstSlotReference);
	FInventoryItem SecondSlotItem = GetItemBySlotReference(InSecondSlotReference);

	SetItemBySlotReference(FirstSlotItem, InSecondSlotReference);
	SetItemBySlotReference(SecondSlotItem, InFirstSlotReference);
}

FInventoryItem InventoryFunctions::GetItemBySlotReference(const InventorySlotReference& InReference)
{
	if(CompoundInventory* Inventory = InReference.AssociatedInventory)
	{
		if (FInventoryBag* Bag = Inventory->GetBag(InReference.BagReference))
		{
			if (Bag->BagSlots.IsValidIndex(InReference.SlotNumberReference))
			{
				return Bag->BagSlots[InReference.SlotNumberReference];
			}
		}
	}
	return FInventoryItem();
}

void InventoryFunctions::SetItemBySlotReference(const FInventoryItem& InItem, const InventorySlotReference& InReference)
{
	if (CompoundInventory* Inventory = InReference.AssociatedInventory)
	{
		if (FInventoryBag* Bag = Inventory->GetBag(InReference.BagReference))
		{
			if (Bag->BagSlots.IsValidIndex(InReference.SlotNumberReference))
			{
				Bag->BagSlots[InReference.SlotNumberReference] = InItem;
				Inventory->Update();
			}
		}
	}
}

int32 InventoryFunctions::GetNumStacksInInventory(const CompoundInventory& InInventory, const FName& InItemID)
{
	int32 AmountFound = 0;
	for (const FInventoryBag& Bag : InInventory.GetAllBags())
	{
		for (const FInventoryItem& Item : Bag.BagSlots)
		{
			if (Item.ItemID == InItemID)
			{
				AmountFound++;
			}
		}
	}

	return AmountFound;
}

bool InventoryFunctions::InventoryContains(const CompoundInventory& InInventory, const FName& InItemID, const int32& InQuantity)
{
	int32 AmountFound = 0;

	for (const FInventoryBag& Bag : InInventory.GetAllBags())
	{
		for (const FInventoryItem& Item : Bag.BagSlots)
		{
			if (Item.ItemID == InItemID)
			{
				AmountFound += Item.Quantity;
			}
		}
	}

	if (AmountFound == InQuantity)
	{
		return true;
	}

	return false;
}

int32 InventoryFunctions::GetNumItemsInInventory(const CompoundInventory& InInventory, const FName& InItemID)
{
	int32 AmountFound = 0;

	for (const FInventoryBag& Bag : InInventory.GetAllBags())
	{
		for (const FInventoryItem& Item : Bag.BagSlots)
		{
			if (Item.ItemID == InItemID)
			{
				AmountFound += Item.Quantity;
			}
		}
	}

	return AmountFound;
}