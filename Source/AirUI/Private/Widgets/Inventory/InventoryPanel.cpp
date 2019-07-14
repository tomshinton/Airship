// Airship Project - Tom Shinton 2018

#include "InventoryPanel.h"
#include <GridSlot.h>

DEFINE_LOG_CATEGORY_STATIC(InventoryPanelLog, Log, Log);

const FName UInventoryPanel::Anim_Show = FName("Show");

UInventoryPanel::UInventoryPanel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Columns(4)
{}

void UInventoryPanel::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (PanelBody && Slots > 0 && SlotClass && Columns > 0)
	{
		PanelBody->ClearChildren();

		for (int32 i = 0; i < Slots; i++)
		{
			if (UInventorySlot* NewSlot = CreateWidget<UInventorySlot>(GetWorld(), SlotClass))
			{
				NewSlot->InventorySlot = i;
				NewSlot->IsHotBarSlot = false;
				NewSlot->SetLinkedInventory(LinkedInventory);

				UGridSlot* AddedChild = PanelBody->AddChildToGrid(NewSlot);

				const int32 TargetRow = i / Columns;
				const int32 TargetColumn = (i % Columns);

				AddedChild->SetRow(TargetRow);
				AddedChild->SetColumn(TargetColumn);
			}
		}
	}
}

void UInventoryPanel::NativeConstruct()
{
	Super::NativeConstruct();

	if (LinkedInventory && PanelBody)
	{
		TArray<UWidget*> ChildWidgets = PanelBody->GetAllChildren();

		for (UWidget* Widget : ChildWidgets)
		{
			if (UInventorySlot* ChildSlot = Cast<UInventorySlot>(Widget))
			{
				ChildSlot->SetLinkedInventory(LinkedInventory);
			}
		}
	}
}