// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySlot.h"
#include "AirChar.h"
#include "AirInventory.h"
#include "Kismet/GameplayStatics.h"
#include <WidgetBlueprintLibrary.h>
#include "Utils/Functions/BindingFunctions.h"
#include "InventorySlotDragOperation.h"

void UInventorySlot::UpdateFocused_Implementation(){}
void UInventorySlot::UpdateFocusCleared_Implementation(){}
void UInventorySlot::UpdateSlotVisuals_Implementation() {}

FInventoryItem UInventorySlot::GetLinkedItem()
{
	if (LinkedInventory.Get())
	{
		return LinkedInventoryItem;
	}

	return FInventoryItem();
}

bool UInventorySlot::OnInventorySlotDrop(UInventorySlotDragOperation* Operation)
{
	UAirInventory* ThisInventory = LinkedInventory.Get();
	UAirInventory* OtherInventory = Operation->SourceInventory;

	const int32 ThisSlotNum = InventorySlot;
	const int32 OtherSlotNum = Operation->IncomingSlot->InventorySlot;

	FInventoryItem OtherInventoryItem = Operation->IncomingSlot->GetLinkedItem();
	FInventoryItem ThisInventoryItem = LinkedInventoryItem;

	OtherInventory->SetItemBySlot(ThisInventoryItem, OtherSlotNum);
	ThisInventory->SetItemBySlot(OtherInventoryItem, ThisSlotNum);

	return true;
}

void UInventorySlot::Build()
{
	Super::Build();

	if (AAirChar* LocalChar = Cast<AAirChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		LinkedInventory = LocalChar->GetInventory();
		if (LinkedInventory.Get())
		{
			LinkedInventory->OnSlotFocusUpdated.AddDynamic(this, &UInventorySlot::PlayerFocusChanged);
			LinkedInventory->OnInventoryUpdated.AddDynamic(this, &UInventorySlot::PlayerInventoryChanged);

			LinkedInventoryItem = LinkedInventory->GetItemBySlot(InventorySlot);
		}
	}
}

void UInventorySlot::PlayerFocusChanged(int32 InSlot)
{
	if (IsHotBarSlot)
	{
		if (InSlot == InventorySlot)
		{
			IsFocused = true;
			UpdateFocused();
		}
		else if (IsFocused)
		{
			IsFocused = false;
			UpdateFocusCleared();
		}
	}
}

void UInventorySlot::PlayerInventoryChanged()
{
	if (LinkedInventory.Get())
	{
		LinkedInventoryItem = LinkedInventory->GetItemBySlot(InventorySlot);
		UpdateSlotVisuals();
	}
}

