// Fill out your copyright notice in the Description page of Project Settings.

#include "AirInventory.h"
#include "WorldItem.h"
#include <GameFramework/Character.h>

UAirInventory::UAirInventory()
	: HotbarSlots(9)
	, InventorySize()
{

}

void UAirInventory::BeginPlay()
{
	Inventory.InventorySize = InventorySize;

	for (int32 i = 0; i < InventorySize; i++)
	{
		Inventory.Inventory.Add(FInventoryItem());
	}

	OnSlotFocusUpdated.Broadcast(0);
}

void UAirInventory::AddItem(const FName ID, const int32 Quantity)
{
	UInventoryFunctions::AddItemFromID(Inventory, ID, Quantity);

	if (OnInventoryUpdated.IsBound())
	{
		OnInventoryUpdated.Broadcast();
	}

	Wield();
}

void UAirInventory::RemoveItem(const FName ID, const int32 Quantity)
{
	UInventoryFunctions::RemoveItem(Inventory, ID, Quantity);

	if (OnInventoryUpdated.IsBound())
	{
		OnInventoryUpdated.Broadcast();
	}

	Wield();
}

void UAirInventory::TransferItem(FName ItemID, int32 Quantity, UAirInventory* RemoveInventory)
{
	if (Quantity > 0 && ItemID != "Item")
	{
		UInventoryFunctions::TransferItems(ItemID, Quantity, RemoveInventory->Inventory, Inventory);

		if (OnInventoryUpdated.IsBound())
		{
			OnInventoryUpdated.Broadcast();
		}

		if (RemoveInventory->OnInventoryUpdated.IsBound())
		{
			RemoveInventory->OnInventoryUpdated.Broadcast();
		}
	}
}

void UAirInventory::Audit(FName ItemID, int32& Stacks, int32& Total)
{
	UInventoryFunctions::Audit(ItemID, Stacks, Total, Inventory);
}

FInventoryItem UAirInventory::GetItemBySlot(const int32 ID)
{
	if (Inventory.Inventory.Num() -1 >= ID)
	{
		return Inventory.Inventory[ID];
	}

	return FInventoryItem();
}

FName UAirInventory::GetItemNameBySlot(const int32 Slot)
{
	if (Inventory.Inventory.Num() - 1 >= Slot)
	{
		const FInventoryItem FoundSlot = Inventory.Inventory[Slot];
		return FoundSlot.ItemID;
	}

	return "";
}

void UAirInventory::FocusNextItem()
{
	CurrFocusedSlot < HotbarSlots-1 ? CurrFocusedSlot++ : CurrFocusedSlot = 0;
	OnSlotFocusUpdated.Broadcast(CurrFocusedSlot);

	Wield();
}

void UAirInventory::FocusLastItem()
{
	CurrFocusedSlot > 0 ? CurrFocusedSlot-- : CurrFocusedSlot = HotbarSlots-1;
	OnSlotFocusUpdated.Broadcast(CurrFocusedSlot);

	Wield();
}

void UAirInventory::Wield()
{
	if (Cast<ACharacter>(GetOwner()))
	{
		FInventoryItem CurrentFocusedItem = Inventory.Inventory[CurrFocusedSlot];

		if (CurrentWieldInterface)
		{
			CurrentWieldInterface->EndWield();
		}

		if (UWorld* World = GetWorld())
		{
			FVector Location = GetOwner()->GetActorLocation();
			FRotator Rotation = GetOwner()->GetActorRotation();
			FActorSpawnParameters SpawnInfo;

			if (AWorldItem* NewSpawnedItem = World->SpawnActor<AWorldItem>(CurrentFocusedItem.GetItemClass(), Location, Rotation, SpawnInfo))
			{
				NewSpawnedItem->AttachToComponent(RightHand, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

				if (IWieldInterface* NewSpawnedItemInterface = Cast<IWieldInterface>(NewSpawnedItem))
				{
					NewSpawnedItemInterface->StartWield();
					CurrentWieldInterface = NewSpawnedItemInterface;
				}
			}
		}
	}
}

void UAirInventory::PrintInventory()
{
	for (FInventoryItem& InventoryItem : Inventory.Inventory)
	{
		InventoryItem.Print();
	}
}

