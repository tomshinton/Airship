// Airship Project - Tom Shinton 2018

#include "Runtime/UI/Public/Widgets/Inventory/InventoryPanel.h"

#include "Runtime/UI/Public/Widgets/Inventory/InventorySlot.h"

#include <AirCore/Public/Core/GameSettings/UISettings.h>
#include <Runtime/Input/Public/AirInputSettings.h>
#include <Runtime/Inventory/Public/InventoryInterface.h>
#include <Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h>
#include <Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h>
#include <Runtime/UMG/Public/Components/CanvasPanelSlot.h>
#include <Runtime/UMG/Public/Components/GridPanel.h>
#include <Runtime/UMG/Public/Components/GridSlot.h>
#include <Runtime/UMG/Public/Components/SizeBox.h>
#include <Runtime/UMG/Public/Components/TextBlock.h>

#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(InventoryPanelLog, Log, Log);

namespace InventoryPanelPrivate
{
	const FName DraggableComponentName = TEXT("DraggableComponent");
}

UInventoryPanel::UInventoryPanel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, PanelBody(nullptr)
	, MoveHandle(nullptr)
	, HandleNameBlock(nullptr)
	, Columns(4)
	, Slots(10)
	, ShowMoveHandle(false)
	, InventoryName()
	, LinkedInventory(nullptr)
	, IsMoving(false)
	, ClickAndDragKey()
	, MouseDragDelta(FVector2D::ZeroVector)
{
	ClickAndDragKey = UAirInputSettings::GetClickAndDragKey();
}

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

	if (MoveHandle)
	{
		if (ShowMoveHandle)
		{
			MoveHandle->SetVisibility(ESlateVisibility::Visible);
		
			if (HandleNameBlock)
			{
				HandleNameBlock->SetText(InventoryName);
			}
		}
		else
		{
			MoveHandle->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

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
						InvViewInterface->SetSlotDomain(SlotDomain);
					}

					UGridSlot* AddedChild = PanelBody->AddChildToGrid(NewSlot);

					  int32 TargetRow = i / Columns;
					const int32 TargetColumn = (i % Columns);

					AddedChild->SetRow(TargetRow);
					AddedChild->SetColumn(TargetColumn);
				}
			}
		}
	}
}