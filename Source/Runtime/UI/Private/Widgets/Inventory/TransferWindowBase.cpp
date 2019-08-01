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
}

void UTransferWindowBase::Build()
{
	Super::Build();

	if (OwnerInventory && OwnerPanel)
	{
		OwnerPanel->SetLinkedInventory((IInventoryInterface*)OwnerInventory.GetInterface());
		OwnerPanel->Build();
	}

	if (PlayerInventory && PlayerPanel)
	{
		PlayerPanel->SetLinkedInventory((IInventoryInterface*)PlayerInventory.GetInterface());
		PlayerPanel->Build();
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
