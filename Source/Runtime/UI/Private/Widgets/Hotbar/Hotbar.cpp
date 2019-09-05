// Airship Project - Tom Shinton 2018

#include "Runtime/UI/Public/Widgets/Hotbar/Hotbar.h"
#include "Runtime/UI/Public/Widgets/Inventory/InventorySlot.h"

#include <AirCore/Public/Core/GameSettings/UISettings.h>
#include <Runtime/UMG/Public/Components/HorizontalBox.h>

UHotbar::UHotbar(const FObjectInitializer& ObjectInitializer)
	: UAirWidget( ObjectInitializer)
	, SlotClass(UInventorySlot::StaticClass())
	, SlotsToAdd(0)
	, Bar(nullptr)
	, SlotDomain(ESlotDomain::Hotbar)
	, HotbarSlotCount(10)
	, LinkedInventory(nullptr)
	, BagID(FGuid())
{}

void UHotbar::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (UUISettings* UISettings = UUISettings::Get())
	{
		SlotClass = UISettings->InventorySlotClass;
	}

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

	if (LinkedInventory && Bar)
	{
		if (const FInventoryBag* HotbarBag = LinkedInventory->GetBagByType(EBagType::Hotbar))
		{
			TArray<UWidget*> ChildWidgets = Bar->GetAllChildren();

			for (UWidget* Widget : ChildWidgets)
			{
				if (UInventorySlot* ChildSlot = Cast<UInventorySlot>(Widget))
				{
					if (ChildSlot->InventorySlot > HotbarBag->GetSlotNum() -1)
					{
						ChildSlot->RemoveFromParent();
					}
					else if (IInventoryViewInterface* SlotViewInterface = Cast<IInventoryViewInterface>(ChildSlot))
					{
						IInventoryInterface* LinkedInventoryInterface = (IInventoryInterface*)LinkedInventory.GetInterface();
						SlotViewInterface->SetLinkedInventory(LinkedInventoryInterface, HotbarBag->GetBagID());
						SlotViewInterface->SetSlotDomain(SlotDomain);

						ChildSlot->Build();
					}
				}
			}
		}
	}
}