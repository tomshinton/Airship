// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySlot.h"
#include "AirChar.h"
#include "AirInventory.h"
#include "Kismet/GameplayStatics.h"

void UInventorySlot::UpdateFocused_Implementation(){}
void UInventorySlot::UpdateFocusCleared_Implementation(){}
void UInventorySlot::UpdateSlotVisuals_Implementation() {}

FInventoryItem UInventorySlot::GetLinkedItem()
{
	if (PlayerInventory)
	{
		return LinkedInventoryItem;
	}

	return FInventoryItem();
}

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (AAirChar* LocalChar = Cast<AAirChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		PlayerInventory = LocalChar->GetInventory();
		if (PlayerInventory)
		{
			PlayerInventory->OnSlotFocusUpdated.AddDynamic(this, &UInventorySlot::PlayerFocusChanged);
			PlayerInventory->OnInventoryUpdated.AddDynamic(this, &UInventorySlot::PlayerInventoryChanged);

			LinkedInventoryItem = PlayerInventory->GetItemBySlot(InventorySlot);
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
	if (PlayerInventory)
	{
		LinkedInventoryItem = PlayerInventory->GetItemBySlot(InventorySlot);
		UpdateSlotVisuals();
	}
}

