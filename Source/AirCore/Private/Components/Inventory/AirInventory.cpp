// Fill out your copyright notice in the Description page of Project Settings.

#include "AirInventory.h"
#include "WorldItem.h"
#include <GameFramework/Character.h>
#include "Utils/Functions/InventoryFunctions.h"

DEFINE_LOG_CATEGORY_STATIC(AirInventoryLog, Log, Log);

UAirInventory::UAirInventory()
	: InventoryName("Default Inventory Name")
	, InventorySize(20)
	, HotbarSlots(0)
{
}

void UAirInventory::BeginPlay()
{
	Inventory.InventorySize = InventorySize;

	for (int32 i = 0; i < InventorySize; i++)
	{
		Inventory.ItemSlots.Add(FInventoryItem());
	}

	if (!Cast<ACharacter>(GetOwner()))
	{
		HotbarSlots = 0;
	}

	OnSlotFocusUpdated.Broadcast(0);

	Super::BeginPlay();
}

void UAirInventory::AddItem(const FName& ID, const int32& Quantity)
{
	UInventoryFunctions::AddItemFromID(Inventory, ID, Quantity);

	if (OnInventoryUpdated.IsBound())
	{
		OnInventoryUpdated.Broadcast();
	}

	Wield();
}

void UAirInventory::RemoveItem(const FName& ID, const int32& Quantity)
{
	UInventoryFunctions::RemoveItem(Inventory, ID, Quantity);

	if (OnInventoryUpdated.IsBound())
	{
		OnInventoryUpdated.Broadcast();
	}

	Wield();
}

void UAirInventory::TransferItem(const FName& ItemID, const int32& Quantity, UAirInventory* ItemToRemoveItemFrom)
{
	if (Quantity > 0 && ItemID != "Item")
	{
		UInventoryFunctions::TransferItems(ItemID, Quantity, Inventory, ItemToRemoveItemFrom->Inventory);

		if (OnInventoryUpdated.IsBound())
		{
			OnInventoryUpdated.Broadcast();
		}

		if (ItemToRemoveItemFrom->OnInventoryUpdated.IsBound())
		{
			ItemToRemoveItemFrom->OnInventoryUpdated.Broadcast();
		}

		//Do we need to wield from the local inventory?
		Wield();

		//Does the removal inventory need to wield?
		ItemToRemoveItemFrom->Wield();
	}
}

void UAirInventory::Audit(const FName& ItemID, int32& Stacks, int32& Total)
{
	UInventoryFunctions::Audit(ItemID, Stacks, Total, Inventory);
}

void UAirInventory::SwapSlots(const int32& FirstSlot, const int32& SecondSlot)
{
	Inventory.ItemSlots.Swap(FirstSlot, SecondSlot);

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
	if (Inventory.ItemSlots.Num() -1 >= ID)
	{
		return Inventory.ItemSlots[ID];
	}

	return FInventoryItem();
}

FName UAirInventory::GetItemNameBySlot(const int32 Slot)
{
	if (Inventory.ItemSlots.Num() - 1 >= Slot)
	{
		const FInventoryItem FoundSlot = Inventory.ItemSlots[Slot];
		return FoundSlot.ItemID;
	}

	return "";
}

void UAirInventory::SetItemBySlot(FInventoryItem InItem, const int32 InSlot)
{
	Inventory.ItemSlots[InSlot] = InItem;

	if (OnInventoryUpdated.IsBound())
	{
		OnInventoryUpdated.Broadcast();
	}

	Wield();
}

void UAirInventory::UpdateFocus()
{
	OnSlotFocusUpdated.Broadcast(CurrFocusedSlot);
	Wield();
}

void UAirInventory::FocusNextItem()
{
	CurrFocusedSlot < HotbarSlots-1 ? CurrFocusedSlot++ : CurrFocusedSlot = 0;
	UpdateFocus();
}

void UAirInventory::FocusLastItem()
{
	CurrFocusedSlot > 0 ? CurrFocusedSlot-- : CurrFocusedSlot = HotbarSlots-1;
	UpdateFocus();
}

void UAirInventory::Wield()
{
	if (Cast<ACharacter>(GetOwner()))
	{
		if (Inventory.ItemSlots.Num() <= 0)
		{
			return;
		}

		FInventoryItem CurrentFocusedItem = Inventory.ItemSlots[CurrFocusedSlot];

		if (CurrentWieldActor)
		{
			if (IWieldInterface* CurrentWieldInterface = Cast<IWieldInterface>(CurrentWieldActor))
			{
				CurrentWieldInterface->EndWield();
			}

			CurrentWieldActor = nullptr;
		}

		if (UWorld* World = GetOwner()->GetWorld())
		{
			const UClass* CurrentWieldClass = CurrentFocusedItem.GetItemClass();

			if (CurrentWieldClass)
			{
				const FVector Location = RightHand->GetComponentLocation();
				const FRotator Rotation = RightHand->GetComponentRotation();
				const FActorSpawnParameters SpawnInfo;

				AWorldItem* NewWieldItem = Cast<AWorldItem>(World->SpawnActor<AWorldItem>(CurrentFocusedItem.GetItemClass(), Location, Rotation, SpawnInfo));
				if (NewWieldItem)
				{
					CurrentWieldActor = NewWieldItem;
					CurrentWieldActor->AttachToComponent(RightHand, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

					CurrentWieldActor->SetAssociatedInventory(this);

					if (IWieldInterface* NewSpawnedItemInterface = Cast<IWieldInterface>(CurrentWieldActor))
					{
						NewSpawnedItemInterface->StartWield();
					}
				}
			}
		}
	}
}

void UAirInventory::StartPrimary()
{
	if (IWieldInterface* CurrentWieldInterface = Cast<IWieldInterface>(CurrentWieldActor))
	{
		CurrentWieldInterface->StartPrimary();
	}
}

void UAirInventory::EndPrimary()
{
	if (IWieldInterface* CurrentWieldInterface = Cast<IWieldInterface>(CurrentWieldActor))
	{
		CurrentWieldInterface->EndPrimary();
	}
}

void UAirInventory::StartSecondary()
{
	if (IWieldInterface* CurrentWieldInterface = Cast<IWieldInterface>(CurrentWieldActor))
	{
		CurrentWieldInterface->StartSecondary();
	}
}

void UAirInventory::EndSecondary()
{
	if (IWieldInterface* CurrentWieldInterface = Cast<IWieldInterface>(CurrentWieldActor))
	{
		CurrentWieldInterface->EndSecondary();
	}
}

void UAirInventory::Reload()
{
	FInventoryItem& CurrItem = Inventory.ItemSlots[CurrFocusedSlot];
	FClip& Clip = CurrItem.Clip;

	if (Clip.ClipSize > 0 && Clip.GetClipCount() < Clip.ClipSize)
	{
		const int32 RoomLeft = Clip.ClipSize - Clip.GetClipCount();
		UE_LOG(AirInventoryLog, Log, TEXT("Currently loading %i %s(s) into %s"), RoomLeft, *Clip.AmmoName.ToString(), *CurrItem.ItemID.ToString());

		const int32 NumRemovedFromInventory = UInventoryFunctions::RemoveItem(Inventory, Clip.AmmoName, RoomLeft).Quantity;

		UE_LOG(AirInventoryLog, Log, TEXT("Removed %i items, ready to load into item"), NumRemovedFromInventory);

		const int32 NewClipCount = Clip.GetClipCount() + NumRemovedFromInventory;
		Clip.SetClipCount(NewClipCount);

		if (OnInventoryUpdated.IsBound())
		{
			OnInventoryUpdated.Broadcast();
			Wield();
		}
	}
	else
	{
		UE_LOG(AirInventoryLog, Log, TEXT("Clip full"));
	}
}

void UAirInventory::ReduceCurrentClip(const int32 InAmountToReduce)
{
	const int32 CurrentClip = Inventory.ItemSlots[CurrFocusedSlot].Clip.CurrentClip;
	const int32 ClipSize = Inventory.ItemSlots[CurrFocusedSlot].Clip.ClipSize;
	Inventory.ItemSlots[CurrFocusedSlot].Clip.CurrentClip = FMath::Clamp<int32>(CurrentClip - InAmountToReduce, 0, ClipSize);

	if (OnInventoryUpdated.IsBound())
	{
		OnInventoryUpdated.Broadcast();
	}
}
