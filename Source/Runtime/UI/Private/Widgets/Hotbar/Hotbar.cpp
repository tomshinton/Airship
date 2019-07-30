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
				Bar->AddChild(NewSlot);
			}
		}
	}
}

void UHotbar::Build()
{
	Super::Build();

	SetHotbarSlotCount();

	if (LinkedInventory && LinkedHotbar && Bar)
	{
		if (LinkedHotbar)
		{
			TArray<UWidget*> ChildWidgets = Bar->GetAllChildren();

			for (UWidget* Widget : ChildWidgets)
			{
				if (UInventorySlot* ChildSlot = Cast<UInventorySlot>(Widget))
				{
					if (ChildSlot->InventorySlot > LinkedHotbar->GetNumHotbarSlots())
					{
						ChildSlot->RemoveFromParent();
					}
					else if (IInventoryViewInterface* SlotViewInterface = Cast<IInventoryViewInterface>(ChildSlot))
					{
						ChildSlot->SetLinkedInventory((IInventoryInterface*)LinkedInventory.GetInterface());
						ChildSlot->Build();
					}
				}
			}
		}
	}
}

void UHotbar::SetHotbarSlotCount()
{
	if (LinkedHotbar)
	{
		HotbarSlotCount = LinkedHotbar->GetNumHotbarSlots();
	}
}
