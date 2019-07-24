// Airship Project - Tom Shinton 2018

#include "InventoryPanel.h"
#include <GridSlot.h>
#include "UISettings.h"
#include "CanvasPanelSlot.h"

DEFINE_LOG_CATEGORY_STATIC(InventoryPanelLog, Log, Log);

const FName UInventoryPanel::Anim_Show = FName("Show");

UInventoryPanel::UInventoryPanel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, PanelBody(nullptr)
	, UseDynamicRows(false)
	, Columns(4)
	, DynamicColumns(0)
	, Slots(10)
{}

void UInventoryPanel::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (UUISettings* UISettings = UUISettings::Get())
	{
		if (PanelBody && Slots > 0 && UISettings->InventorySlotClass && (Columns > 0 || UseDynamicRows))
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
						InvViewInterface->SetLinkedInventory(LinkedInventory);
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

void UInventoryPanel::SetDynamicColumns()
{
	if(UWidget* ParentWidget = GetParent())
	{
			const float ParentWidth = ParentWidget->GetDesiredSize().X;
	}
	else
	{
		UseDynamicRows = false;
	}
}
