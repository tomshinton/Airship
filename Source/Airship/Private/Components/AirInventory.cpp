// Fill out your copyright notice in the Description page of Project Settings.

#include "AirInventory.h"
#include "WorldItem.h"
#include <GameFramework/Character.h>

UAirInventory::UAirInventory()
	: HotbarSlots(0)
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

	if (!Cast<ACharacter>(GetOwner()))
	{
		HotbarSlots = 0;
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

		//Do we need to wield from the local inventory?
		Wield();

		//Does the removal inventory need to wield?
		RemoveInventory->Wield();
	}
}

void UAirInventory::Audit(FName ItemID, int32& Stacks, int32& Total)
{
	UInventoryFunctions::Audit(ItemID, Stacks, Total, Inventory);
}

void UAirInventory::SwapSlots(const int32 FirstSlot, const int32 SecondSlot)
{
	Inventory.Inventory.Swap(FirstSlot, SecondSlot);

	if (OnInventoryUpdated.IsBound())
	{
		OnInventoryUpdated.Broadcast();
	}

	Wield();
}

void UAirInventory::GetBackpackBounds(bool& HasBackpackSlots, int32& BackpackStart, int32& BackpackEnd)
{
	if (InventorySize - 1 <= HotbarSlots)
	{
		HasBackpackSlots = false;
		return;
	}

	HasBackpackSlots = true;
	BackpackStart = FMath::Clamp(HotbarSlots, 0, InventorySize);
	BackpackEnd = InventorySize - 1;
}

void UAirInventory::GetHotbarBounds(bool& HasHotbarSlots, int32& HotbarStart, int32& HotbarEnd)
{
	if (HotbarSlots == 0)
	{
		HasHotbarSlots = false;
		return;
	}
	
	HasHotbarSlots = true;
	HotbarStart = 0;
	HotbarEnd = FMath::Clamp(HotbarSlots - 1, 0, InventorySize-1);
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

void UAirInventory::SetItemBySlot(FInventoryItem InItem, const int32 InSlot)
{
	Inventory.Inventory[InSlot] = InItem;

	if (OnInventoryUpdated.IsBound())
	{
		OnInventoryUpdated.Broadcast();
	}

	Wield();
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

		if (CurrentWieldActor.Get())
		{
			if (IWieldInterface* CurrentWieldInterface = Cast<IWieldInterface>(CurrentWieldActor.Get()))
			{
				CurrentWieldInterface->EndWield();
			}
		}

		if (UWorld* World = GetOwner()->GetWorld())
		{
			FVector Location = GetOwner()->GetActorLocation();
			FRotator Rotation = GetOwner()->GetActorRotation();
			FActorSpawnParameters SpawnInfo;

			AWorldItem* NewWieldItem = Cast<AWorldItem>(World->SpawnActor<AWorldItem>(CurrentFocusedItem.GetItemClass(), Location, Rotation, SpawnInfo));
			if(NewWieldItem)
			{
				CurrentWieldActor = NewWieldItem;
				CurrentWieldActor->AttachToComponent(RightHand, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

				if(IWieldInterface* NewSpawnedItemInterface = Cast<IWieldInterface>(CurrentWieldActor.Get()))
				{
					NewSpawnedItemInterface->StartWield();
				}
			}
		}
	}
}

void UAirInventory::StartPrimary()
{
	if (IWieldInterface* CurrentWieldInterface = Cast<IWieldInterface>(CurrentWieldActor.Get()))
	{
		CurrentWieldInterface->StartPrimary();
	}
}

void UAirInventory::EndPrimary()
{
	if (IWieldInterface* CurrentWieldInterface = Cast<IWieldInterface>(CurrentWieldActor.Get()))
	{
		CurrentWieldInterface->EndPrimary();
	}
}

void UAirInventory::StartSecondary()
{
	if (IWieldInterface* CurrentWieldInterface = Cast<IWieldInterface>(CurrentWieldActor.Get()))
	{
		CurrentWieldInterface->StartSecondary();
	}
}

void UAirInventory::EndSecondary()
{
	if (IWieldInterface* CurrentWieldInterface = Cast<IWieldInterface>(CurrentWieldActor.Get()))
	{
		CurrentWieldInterface->EndSecondary();
	}
}
