// Airship Project - Tom Shinton 2018

#include "InventoryPanel.h"
#include <GridSlot.h>
#include "UISettings.h"
#include "CanvasPanelSlot.h"

DEFINE_LOG_CATEGORY_STATIC(InventoryPanelLog, Log, Log);

UInventoryPanel::UInventoryPanel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, PanelBody(nullptr)
	, Columns(4)
	, DynamicColumns(0)
	, Slots(10)
{}

void UInventoryPanel::Build()
{
	if (PanelBody)
	{
		if (PanelBody->GetAllChildren().Num() < LinkedInventory->GetInventorySlotCount())
		{
			UE_LOG(InventoryPanelLog, Warning, TEXT("%s not configured to handle an inventory of this size - attempting to rebuild with the correct number of slots at runtime"), *GetName());
			UE_LOG(InventoryPanelLog, Warning, TEXT("We need %i slots - we only have %i"), LinkedInventory->GetInventorySlotCount(), PanelBody->GetAllChildren().Num());
	
			Slots = LinkedInventory->GetInventorySlotCount();
			SynchronizeProperties();
		}
	}

	if (LinkedInventory && PanelBody)
	{
		for (UWidget* Widget : PanelBody->GetAllChildren())
		{
			if (UInventorySlot* ChildSlot = Cast<UInventorySlot>(Widget))
			{
				if (ChildSlot->InventorySlot > LinkedInventory->GetInventorySlotCount())
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

void UInventoryPanel::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (UUISettings* UISettings = UUISettings::Get())
	{
		if (PanelBody && Slots > 0 && UISettings->InventorySlotClass)
		{
			PanelBody->ClearChildren();

			for (int32 i = 0; i < Slots; i++)
			{
				if (UInventorySlot* NewSlot = CreateWidget<UInventorySlot>(GetWorld(), UISettings->InventorySlotClass))
				{
					NewSlot->InventorySlot = i;
					NewSlot->IsHotBarSlot = false;

					if (IInventoryViewInterface* InvViewInterface = Cast<IInventoryViewInterface>(NewSlot))
					{
						InvViewInterface->SetLinkedInventory((IInventoryInterface*)LinkedInventory.GetInterface());
					}

					UGridSlot* AddedChild = PanelBody->AddChildToGrid(NewSlot);

					const int32 TargetRow = i / Columns;
					const int32 TargetColumn = (i % Columns);

					AddedChild->SetRow(TargetRow);
					AddedChild->SetColumn(TargetColumn);
				}
			}
		}
	}
}