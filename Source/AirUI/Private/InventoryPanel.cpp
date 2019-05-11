// Airship Project - Tom Shinton 2018

#include "InventoryPanel.h"
#include <GridSlot.h>

DEFINE_LOG_CATEGORY_STATIC(InventoryPanelLog, Log, Log);

UInventoryPanel::UInventoryPanel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Columns(1)
{}

void UInventoryPanel::NativeConstruct()
{
	Super::NativeConstruct();

	if (LinkedInventory && PanelBody)
	{
		if (Columns > 0)
		{
			for (int32 i = 0; i < LinkedInventory->GetInventorySize(); i++)
			{
				if (UInventorySlot* NewSlot = CreateWidget<UInventorySlot>(GetWorld(), SlotClass))
				{
					NewSlot->InventorySlot = i;
					NewSlot->IsHotBarSlot = false;
					NewSlot->SetLinkedInventory(LinkedInventory);

					UGridSlot* AddedChild = PanelBody->AddChildToGrid(NewSlot);

					int32 TotalSlots = LinkedInventory->GetInventorySize();

					const int32 TargetRow = i / Columns;
					const int32 TargetColumn = (i % Columns);

					AddedChild->SetRow(TargetRow);
					AddedChild->SetColumn(TargetColumn);
				}
			}
		}
	}
}