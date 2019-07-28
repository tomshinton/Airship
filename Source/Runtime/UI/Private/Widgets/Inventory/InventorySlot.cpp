// Airship Project - Tom Shinton 2018

#include "InventorySlot.h"
#include "AirChar.h"
#include "AirInventory.h"
#include "Kismet/GameplayStatics.h"
#include <WidgetBlueprintLibrary.h>
#include "Utils/Functions/BindingFunctions.h"
#include "InventorySlotDragOperation.h"
#include <Engine/DataTable.h>
#include <Image.h>
#include <TextBlock.h>
#include "DragAndDropVisual.h"
#include "InventorySettings.h"
#include "UISettings.h"
#include "CanvasPanelSlot.h"
#include "SizeBox.h"

void UInventorySlot::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (UUISettings* UISettings = UUISettings::Get())
	{
		if (SlotBody)
		{
			if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SlotBody->Slot))
			{
				CanvasSlot->SetSize(FVector2D(UISettings->InventorySlotSize, UISettings->InventorySlotSize));
			}
		}
	}
}

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	BuildSlotVisuals();

	if (!LinkedInventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("Build called on inventory slot before having its LinkedInventory set!"));
	}

	if (LinkedInventory)
	{
		LinkedInventory->OnSlotFocusUpdated.AddLambda([this](const int32 NewSlot)
		{
			PlayerFocusChanged(NewSlot);
		});

		LinkedInventory->OnInventoryUpdated.AddLambda([this]()
		{
			PlayerInventoryChanged();
		});

		const int32 FocusedSlot = LinkedInventory->GetCurrentFocusedSlot();
		PlayerFocusChanged(FocusedSlot);

		LinkedInventoryItem = LinkedInventory->GetItemBySlot(InventorySlot);
	}
}

FInventoryItem UInventorySlot::GetLinkedItem()
{
	if (LinkedInventory)
	{
		return LinkedInventoryItem;
	}

	return FInventoryItem();
}

bool UInventorySlot::OnInventorySlotDrop(UInventorySlotDragOperation* Operation)
{
	UAirInventory* ThisInventory = LinkedInventory;
	UAirInventory* OtherInventory = Operation->SourceInventory;

	const int32 ThisSlotNum = InventorySlot;
	const int32 OtherSlotNum = Operation->IncomingSlot->InventorySlot;

	FInventoryItem OtherInventoryItem = Operation->IncomingSlot->GetLinkedItem();
	FInventoryItem ThisInventoryItem = LinkedInventoryItem;

	if (OtherInventory && ThisInventory)
	{
		OtherInventory->SetItemBySlot(ThisInventoryItem, OtherSlotNum);
		ThisInventory->SetItemBySlot(OtherInventoryItem, ThisSlotNum);

		return true;
	}
	else
	{
		return false;
	}
}

void UInventorySlot::SetInventorySlot(const int32 InSlot, bool InIsHotbarSlot)
{
	InventorySlot = InSlot;
	IsHotBarSlot = InIsHotbarSlot;
}

void UInventorySlot::PlayerFocusChanged(int32 InSlot)
{
	if (IsHotBarSlot)
	{
		if (InSlot == InventorySlot)
		{
			IsFocused = true;

			PlayAnimation(FocusAnim);
		}
		else if (IsFocused)
		{
			IsFocused = false;

			PlayAnimation(FocusAnim, 0.f, 1, EUMGSequencePlayMode::Reverse, 3.f);
		}
	}
}

void UInventorySlot::PlayerInventoryChanged()
{
	if (LinkedInventory)
	{
		LinkedInventoryItem = LinkedInventory->GetItemBySlot(InventorySlot);
		BuildSlotVisuals();
	}
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (IsPopulated && DragAndDropVisual)
	{
		if (UDragAndDropVisual* DragAndDropWidget = CreateWidget<UDragAndDropVisual>(GetWorld(), DragAndDropVisual))
		{
			DragAndDropWidget->SetVisual(QuantityText->GetText(), ItemIcon->Brush);

			if (UInventorySlotDragOperation* DragOp = Cast<UInventorySlotDragOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(UInventorySlotDragOperation::StaticClass())))
			{
				DragOp->DefaultDragVisual = DragAndDropWidget;
				DragOp->IncomingSlot = this;
				DragOp->SourceInventory = LinkedInventory;

				OutOperation = DragOp;
			}
		}
	}
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (UInventorySlotDragOperation* DropOp = Cast<UInventorySlotDragOperation>(InOperation))
	{
		OnInventorySlotDrop(DropOp);
		return true;
	}

	return false;
}

void UInventorySlot::BuildSlotVisuals()
{
	if(UDataTable* InventoryDataTable = UInventorySettings::GetItemLookupTable())
	{
		const FString ContextString = "Item Lookup";
		FInventoryItemRow* FoundRow = InventoryDataTable->FindRow<FInventoryItemRow>(LinkedInventoryItem.ItemID, ContextString, false);

		if (FoundRow)
		{
			BuildFromValidData(FoundRow);
		}
		else
		{
			BuildFromInvalidData();
		}
	}
}

void UInventorySlot::BuildFromValidData(FInventoryItemRow* Row)
{
	ItemIcon->SetVisibility(ESlateVisibility::Visible);
	QuantityText->SetVisibility(ESlateVisibility::Visible);
	ClipText->SetVisibility(ESlateVisibility::Visible);

	ItemIcon->SetBrushFromTexture(Row->ItemIcon, true);

	const FString QuantityString = FString::FromInt(LinkedInventoryItem.Quantity);
	QuantityText->SetText(FText::FromString(QuantityString));

	if (Row->Clip.ClipSize > 0)
	{
		const FString ClipString = FString::FromInt(LinkedInventoryItem.Clip.CurrentClip) + "/" + FString::FromInt(Row->Clip.ClipSize);
		ClipText->SetText(FText::FromString(ClipString));
	}
	else
	{
		ClipText->SetVisibility(ESlateVisibility::Hidden);
	}

	IsPopulated = true;
}

void UInventorySlot::BuildFromInvalidData()
{
	if (ItemIcon)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);
	}

	if (QuantityText)
	{
		QuantityText->SetVisibility(ESlateVisibility::Hidden);
	}

	if (ClipText)
	{
		ClipText->SetVisibility(ESlateVisibility::Hidden);
	}

	IsPopulated = false;
}

