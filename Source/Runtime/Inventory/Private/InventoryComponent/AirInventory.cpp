// Airship Project - Tom Shinton 2018

#include "Runtime/Inventory/Public/InventoryComponent/AirInventory.h"
#include "Runtime/Inventory/Public/InventoryFunctions.h"
#include "Runtime/Inventory/Public/InventoryTypes/InventoryItem.h"

#include <Runtime/Engine/Classes/GameFramework/Character.h>
#include <Runtime/Item/Public/WieldInterface.h>
#include <Runtime/Item/Public/WorldItem.h>

DEFINE_LOG_CATEGORY_STATIC(AirInventoryLog, Log, Log);

UAirInventory::UAirInventory()
	: InventoryName("Default Inventory Name")
	, DefaultBags()
	, OnInventoryUpdated()
	, OnSlotFocusUpdated()
	, Inventory(DefaultBags, 10)
	, CurrFocusedSlot()
	, CurrentWieldActor(nullptr)
	, IsAiming(false)
{}

void UAirInventory::BeginPlay()
{
	OnSlotFocusUpdated.Broadcast(0);

	Super::BeginPlay();
}

void UAirInventory::AddBag(const FInventoryBag& InNewBag)
{
	Inventory.AddBag(InNewBag);
}

void UAirInventory::AddItem(const FName& ID, const int32& Quantity)
{
	InventoryFunctions::AddItemFromID(Inventory, ID, Quantity);

	if (OnInventoryUpdated.IsBound())
	{
		OnInventoryUpdated.Broadcast();
	}

	Wield();
}

void UAirInventory::RemoveItem(const FName& ID, const int32& Quantity)
{
	InventoryFunctions::RemoveItemFromID(Inventory, ID, Quantity);

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
		InventoryFunctions::TransferItems(ItemID, Quantity, Inventory, ItemToRemoveItemFrom->Inventory);

		if (OnInventoryUpdated.IsBound())
		{
			OnInventoryUpdated.Broadcast();
		}

		if (ItemToRemoveItemFrom->OnInventoryUpdated.IsBound())
		{
			ItemToRemoveItemFrom->OnInventoryUpdated.Broadcast();
		}

		Wield();
		ItemToRemoveItemFrom->Wield();
	}
}

void UAirInventory::SwapSlots(const int32& FirstSlot, const int32& SecondSlot)
{
	/*Inventory.GetAllSlots().Swap(FirstSlot, SecondSlot);

	if (OnInventoryUpdated.IsBound())
	{
		OnInventoryUpdated.Broadcast();
	}

	Wield();*/
}

FInventoryItem UAirInventory::GetItemBySlot(const FGuid& InBagID, const int32 InSlot) const
{
	if (FInventoryBag* FoundBag = Inventory.GetBag(InBagID))
	{
		return FoundBag->GetSlotByIndex(InSlot);
	}

	return FInventoryItem();
}

FName UAirInventory::GetItemNameBySlot(const int32& Slot) const
{
	/*if (Inventory.GetAllSlots().Num() - 1 >= Slot)
	{
		const FInventoryItem FoundSlot = Inventory.GetAllSlots()[Slot];
		return FoundSlot.ItemID;
	}*/

	return FName();
}

void UAirInventory::SetItemBySlot(const FInventoryItem& InItem, const int32 InSlot)
{
	/*Inventory.GetAllSlots()[InSlot] = InItem;

	if (OnInventoryUpdated.IsBound())
	{
		OnInventoryUpdated.Broadcast();
	}

	Wield();*/
}

int32 UAirInventory::GetInventorySlotCount() const
{
	//return Inventory.GetAllSlots().Num();

	return 0;
}

FGuid UAirInventory::GetBagIDByIndex(const int32 InIndex) const
{
	FInventoryBag NewBag;
	if (Inventory.GetBag(InIndex, NewBag))
	{
		return NewBag.GetBagID();
	}

	return FGuid();
}

FGuid UAirInventory::GetFirstPrimaryBagID() const
{
	const int32 IndexOfFirstPrimary = Inventory.GetAllBags().IndexOfByPredicate([](const FInventoryBag& Bag)
	{
		return Bag.GetIsPrimary() && Bag.GetBagType() != EBagType::Hotbar;
	});

	if (IndexOfFirstPrimary != INDEX_NONE)
	{
		return Inventory.GetAllBags()[IndexOfFirstPrimary].GetBagID();
	}

	return FGuid();
}

const FInventoryBag* UAirInventory::GetBagByType(const EBagType& InBagType) const
{
	return Inventory.GetBagByType(InBagType);
}

const FInventoryBag* UAirInventory::GetBagByID(const FGuid& InBagID) const
{
	return Inventory.GetBag(InBagID);
}

void UAirInventory::UpdateFocus()
{
	OnSlotFocusUpdated.Broadcast(CurrFocusedSlot);
	Wield();
}

void UAirInventory::FocusNextItem()
{
	if (const FInventoryBag* HotbarBag = Inventory.GetBagByType(EBagType::Hotbar))
	{
		CurrFocusedSlot < HotbarBag->GetSlotNum() - 1 ? CurrFocusedSlot++ : CurrFocusedSlot = 0;
		UpdateFocus();
	}
}

void UAirInventory::FocusLastItem()
{
	if (const FInventoryBag* HotbarBag = Inventory.GetBagByType(EBagType::Hotbar))
	{
		CurrFocusedSlot > 0 ? CurrFocusedSlot-- : CurrFocusedSlot = HotbarBag->GetSlotNum() - 1;
		UpdateFocus();
	}
}

void UAirInventory::Wield()
{
	/*if (Cast<ACharacter>(GetOwner()))
	{
		if (Inventory.GetAllSlots().Num() <= 0)
		{
			return;
		}

		FInventoryItem CurrentFocusedItem = Inventory.GetAllSlots()[CurrFocusedSlot];

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
	}*/
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
	/*if (FInventoryBag* HotbarBag = const_cast<FInventoryBag*>(Inventory.GetBagByType(EBagType::Hotbar)))
	{
		FInventoryItem& CurrItem = HotbarBag->GetSlotByIndex(CurrFocusedSlot);
		FClip& Clip = CurrItem.Clip;

		const int32 ClipCount = Clip.GetClipCount();
		if (Clip.ClipSize > 0 && ClipCount < Clip.ClipSize)
		{
			const int32 RoomLeft = Clip.ClipSize - Clip.GetClipCount();
			const int32 NumRemovedFromInventory = InventoryFunctions::RemoveItemFromID(Inventory, Clip.AmmoName, RoomLeft).Quantity;

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
	}*/
}

void UAirInventory::ReduceCurrentClip(const int32 InAmountToReduce)
{
	//We can only focus slots that're on the hotbar
	if (FInventoryBag* HotbarBag = const_cast<FInventoryBag*>(Inventory.GetBagByType(EBagType::Hotbar)))
	{
		const int32 CurrentClip = HotbarBag->GetSlotByIndex(CurrFocusedSlot).Clip.CurrentClip;
		const int32 ClipSize = HotbarBag->GetSlotByIndex(CurrFocusedSlot).Clip.ClipSize;
		HotbarBag->GetSlotByIndex(CurrFocusedSlot).Clip.CurrentClip = FMath::Clamp<int32>(CurrentClip - InAmountToReduce, 0, ClipSize);

		if (OnInventoryUpdated.IsBound())
		{
			OnInventoryUpdated.Broadcast();
		}
	}
}
