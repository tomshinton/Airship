// Airship Project - Tom Shinton 2018

#include "Hotbar.h"
#include "InventorySlot.h"
#include <HorizontalBox.h>
#include "AirWidget.h"

UHotbar::UHotbar(const FObjectInitializer& ObjectInitializer)
	: Super( ObjectInitializer)
	, HotbarSlotCount(0)
{

}

void UHotbar::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (SlotsToAdd > 0 && Bar && SlotClass)
	{
		Bar->ClearChildren();

		for (int32 i = 0; i < SlotsToAdd; i++)
		{
			if (UInventorySlot* NewSlot = CreateWidget<UInventorySlot>(GetWorld(), SlotClass))
			{
				NewSlot->InventorySlot = i;
				NewSlot->IsHotBarSlot = true;
				NewSlot->SetLinkedInventory(LinkedInventory);

				Bar->AddChild(NewSlot);
			}
		}
	}
}

void UHotbar::NativeConstruct()
{
	Super::NativeConstruct();

	SetHotbarSlotCount();

	if (LinkedInventory && Bar)
	{
		TArray<UWidget*> ChildWidgets = Bar->GetAllChildren();

		for (UWidget* Widget : ChildWidgets)
		{
			if (UInventorySlot* ChildSlot = Cast<UInventorySlot>(Widget))
			{
				if (ChildSlot->InventorySlot > HotbarSlotCount)
				{
					ChildSlot->RemoveFromParent();
				}
				else
				{
					ChildSlot->SetLinkedInventory(LinkedInventory);
				}
			}
		}
	}
}

void UHotbar::SetHotbarSlotCount()
{
	if (LinkedInventory)
	{
		HotbarSlotCount = LinkedInventory->HotbarSlots;
	}
}
