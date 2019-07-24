// Fill out your copyright notice in the Description page of Project Settings.

#include "TransferWindowBase.h"
#include "UISettings.h"
#include "GridSlot.h"
#include "InventoryPanel.h"

void UTransferWindowBase::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UTransferWindowBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (OwnerInventory && OwnerPanel)
	{
		OwnerPanel->SetLinkedInventory(OwnerInventory);
	}

	if (PlayerInventory && PlayerPanel)
	{
		OwnerPanel->SetLinkedInventory(PlayerInventory);
	}
}