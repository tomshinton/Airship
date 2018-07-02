// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySlot.h"
#include "AirChar.h"
#include "AirInventory.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/InventoryFunctions.h"

void UInventorySlot::UpdateFocused_Implementation(){}
void UInventorySlot::UpdateFocusCleared_Implementation(){}
void UInventorySlot::UpdateSlotVisuals_Implementation() {}

FInventoryItem UInventorySlot::GetLinkedItem()
{
	if (PlayerInventory)
	{
		return PlayerInventory->GetItemByID(InventorySlot);
	}

	return FInventoryItem(0, 0);
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

			LinkedInventoryItem = PlayerInventory->GetItemByID(InventorySlot);
		}
	}
}

void UInventorySlot::PlayerFocusChanged(int32 InSlot)
{
	if (InSlot == InventorySlot)
	{
		IsFocused = true;
		UpdateFocused();
	}
	else if(IsFocused)
	{
		IsFocused = false;
		UpdateFocusCleared();
	}
}

void UInventorySlot::PlayerInventoryChanged()
{
	if (PlayerInventory)
	{
		UpdateSlotVisuals();
	}
}

