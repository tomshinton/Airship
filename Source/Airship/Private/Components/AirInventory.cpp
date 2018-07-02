// Fill out your copyright notice in the Description page of Project Settings.

#include "AirInventory.h"

UAirInventory::UAirInventory()
	: HotbarSlots(9)
{

}

void UAirInventory::AddItem(const int32 ID, const int32 Quantity)
{
	UInventoryFunctions::AddItemFromID(Inventory, ID, Quantity);

	if (OnInventoryUpdated.IsBound())
	{
		OnInventoryUpdated.Broadcast();
	}
}

void UAirInventory::RemoveItem(const int32 ID, const int32 Quantity)
{
	UInventoryFunctions::RemoveItem(Inventory, ID, Quantity);

	if (OnInventoryUpdated.IsBound())
	{
		OnInventoryUpdated.Broadcast();
	}
}

FInventoryItem UAirInventory::GetItemByID(const int32 ID)
{
	if (Inventory.Inventory.Num() -1 >= ID)
	{
		return Inventory.Inventory[ID];
	}

	return FInventoryItem();
}

void UAirInventory::FocusNextItem()
{
	CurrFocusedSlot < HotbarSlots-1 ? CurrFocusedSlot++ : CurrFocusedSlot = 0;
	OnSlotFocusUpdated.Broadcast(CurrFocusedSlot);
}

void UAirInventory::FocusLastItem()
{
	CurrFocusedSlot > 0 ? CurrFocusedSlot-- : CurrFocusedSlot = HotbarSlots-1;
	OnSlotFocusUpdated.Broadcast(CurrFocusedSlot);
}

void UAirInventory::BeginPlay()
{
	OnSlotFocusUpdated.Broadcast(0);
}
