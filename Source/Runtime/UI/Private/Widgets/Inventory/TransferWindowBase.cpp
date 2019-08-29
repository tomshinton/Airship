// Airship Project - Tom Shinton 2018

#include "Runtime/UI/Public/Widgets/Inventory/TransferWindowBase.h"
#include "Runtime/UI/Public/Widgets/Inventory/InventoryPanel.h"

#include <AirCore/Public/Core/GameSettings/UISettings.h>
#include <Runtime/UMG/Public/Components/GridSlot.h>

UTransferWindowBase* UTransferWindowBase::NewWindow(IInventoryInterface& OwningInterface, IInventoryInterface& PlayerInterface, UWorld& WorldContext)
{
	if (UUISettings* UISettings = UUISettings::Get())
	{
		if (UISettings->TransferWindowClass)
		{
			if (UTransferWindowBase* TransferUI = CreateWidget<UTransferWindowBase>(&WorldContext, UISettings->TransferWindowClass))
			{
				TransferUI->SetOwningInventory(&OwningInterface);
				TransferUI->SetPlayerInventory(&PlayerInterface);

				return TransferUI;
			}
		}
	}

	return nullptr;
}

void UTransferWindowBase::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (OwnerPanel)
	{
		OwnerPanel->SetSlotDomain(ESlotDomain::TransferWindow);
	}

	if (PlayerPanel)
	{
		OwnerPanel->SetSlotDomain(ESlotDomain::TransferWindow);
	}
}

void UTransferWindowBase::Build()
{
	Super::Build();

	if (OwnerInventory && OwnerPanel)
	{
		if (IInventoryInterface* OwnerInventoryInterface = (IInventoryInterface*)OwnerInventory.GetInterface())
		{
			OwnerPanel->SetLinkedInventory(OwnerInventoryInterface, OwnerInventoryInterface->GetFirstPrimaryBagID());
			OwnerPanel->Build();
		}
	}

	if (PlayerInventory && PlayerPanel)
	{
		if (IInventoryInterface* PlayerInventoryInterface = (IInventoryInterface*)PlayerInventory.GetInterface())
		{
			PlayerPanel->SetLinkedInventory(PlayerInventoryInterface, PlayerInventoryInterface->GetFirstPrimaryBagID());
			PlayerPanel->Build();
		}
	}
}

void UTransferWindowBase::SetOwningInventory(IInventoryInterface* OwningInterface)
{
	OwnerInventory.SetInterface(OwningInterface);
	OwnerInventory.SetObject(this);
}

void UTransferWindowBase::SetPlayerInventory(IInventoryInterface* PlayerInterface)
{
	PlayerInventory.SetInterface(PlayerInterface);
	PlayerInventory.SetObject(this);
}

bool UTransferWindowBase::ShouldLockOverlay() const
{
	return true;
}