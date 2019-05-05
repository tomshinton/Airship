// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySlot.h"
#include "AirChar.h"
#include "AirInventory.h"
#include "Kismet/GameplayStatics.h"
#include <WidgetBlueprintLibrary.h>
#include "Utils/Functions/BindingFunctions.h"
#include "InventorySlotDragOperation.h"
#include "AirSettings.h"
#include <Engine/DataTable.h>
#include "Utils/Datatypes/InventoryItems.h"

#include <Image.h>
#include <TextBlock.h>
#include "DragAndDropVisual.h"

void UInventorySlot::UpdateFocused_Implementation(){}
void UInventorySlot::UpdateFocusCleared_Implementation(){}

void UInventorySlot::UpdateSlotVisuals_Implementation() 
{
	BuildSlotVisuals();
}

FInventoryItem UInventorySlot::GetLinkedItem()
{
	if (LinkedInventory.Get())
	{
		return LinkedInventoryItem;
	}

	return FInventoryItem();
}

bool UInventorySlot::OnInventorySlotDrop(UInventorySlotDragOperation* Operation)
{
	UAirInventory* ThisInventory = LinkedInventory.Get();
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
	
	UpdateSlotVisuals();
}

void UInventorySlot::Build()
{
	Super::Build();

	if (AAirChar* LocalChar = Cast<AAirChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{

		if (!LinkedInventory.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("Build called on inventory slot before having its LinkedInventory set!"));
		}


		if (LinkedInventory.Get())
		{
			LinkedInventory->OnSlotFocusUpdated.AddDynamic(this, &UInventorySlot::PlayerFocusChanged);
			LinkedInventory->OnInventoryUpdated.AddDynamic(this, &UInventorySlot::PlayerInventoryChanged);

			LinkedInventoryItem = LinkedInventory->GetItemBySlot(InventorySlot);
		}
	}
}

void UInventorySlot::PlayerFocusChanged(int32 InSlot)
{
	if (IsHotBarSlot)
	{
		if (InSlot == InventorySlot)
		{
			IsFocused = true;
			UpdateFocused();
		}
		else if (IsFocused)
		{
			IsFocused = false;
			UpdateFocusCleared();
		}
	}
}

void UInventorySlot::PlayerInventoryChanged()
{
	if (LinkedInventory.Get())
	{
		LinkedInventoryItem = LinkedInventory->GetItemBySlot(InventorySlot);
		UpdateSlotVisuals();
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
				DragOp->SourceInventory = LinkedInventory.Get();

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
	if (UAirSettings* GameSettings = GetMutableDefault<UAirSettings>())
	{
		if (UDataTable* InventoryDataTable = Cast<UDataTable>(GameSettings->InventoryLookup.TryLoad()))
		{
			FString ContextString = "Item Lookup";
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
	ItemIcon->SetVisibility(ESlateVisibility::Hidden);
	QuantityText->SetVisibility(ESlateVisibility::Hidden);
	ClipText->SetVisibility(ESlateVisibility::Hidden);

	IsPopulated = false;
}

