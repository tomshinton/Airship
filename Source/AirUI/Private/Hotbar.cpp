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

void UHotbar::NativeConstruct()
{
	Super::NativeConstruct();

	SetHotbarSlotCount();

	if (SlotsToAdd > 0 && Bar && SlotClass)
	{
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

void UHotbar::SetHotbarSlotCount()
{
	if (LinkedInventory)
	{
		HotbarSlotCount = LinkedInventory->HotbarSlots;
	}
}
