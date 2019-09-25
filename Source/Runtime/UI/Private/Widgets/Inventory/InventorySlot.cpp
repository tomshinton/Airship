// Airship Project - Tom Shinton 2018

#include "Runtime/UI/Public/Widgets/Inventory/InventorySlot.h"

#include "Runtime/UI/Public/DragAndDrop/InventorySlotDragOperation.h"
#include "Runtime/UI/Public/DragAndDrop/DragAndDropVisual.h"
#include "Runtime/UI/Public/QuickTransfer/TransferRequest.h"

#include <AirCore/Public/Core/GameSettings/UISettings.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/Inventory/Public/InventoryFunctions.h>
#include <Runtime/Inventory/Public/InventoryTypes/InventorySlotReference.h>
#include <Runtime/Input/Public/AirInputSettings.h>
#include <Runtime/Inventory/Public/InventorySettings.h>
#include <Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h>
#include <Runtime/UMG/Public/Components/CanvasPanelSlot.h>
#include <Runtime/UMG/Public/Components/SizeBox.h>
#include <Runtime/Utils/Public/Input/BindingFunctions.h>

DEFINE_LOG_CATEGORY(InventorySlotLog);

UInventorySlot::UInventorySlot(const FObjectInitializer& ObjectInitializer)
	: UAirWidget(ObjectInitializer)
	, SlotBody(nullptr)
	, ClipText(nullptr)
	, ItemIcon(nullptr)
	, QuantityText(nullptr)
	, FocusAnim(nullptr)
	, InventorySlot(0)
	, IsHotBarSlot(0)
	, IsPopulated(0)
	, DragAndDropVisual(UDragAndDropVisual::StaticClass())
	, SlotDomain(ESlotDomain::Default)
	, LinkedInventory()
	, IsFocused(false)
	, ClickAndDragKey()
	, LinkedInventoryItem()
	, SlotChordLookup(*this)
	, BagID(FGuid())
{
	ClickAndDragKey = UAirInputSettings::GetClickAndDragKey();
}

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

InventorySlotReference UInventorySlot::GetSlotRef()
{
	if (LinkedInventory)
	{
		return InventorySlotReference(LinkedInventory->GetInventory(), BagID, InventorySlot);
	}

	UE_LOG(InventorySlotLog, Error, TEXT("Attempted to get the SlotReference from a slot with no valid linked inventory - returning a null reference"));
	return InventorySlotReference();
}

void UInventorySlot::Build()
{
	SlotChordLookup.Bind({ ClickAndDragKey, EKeys::LeftShift },
	[this]()
	{
		QuickTransfer();
	});

	if (!LinkedInventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("Build called on inventory slot before having its LinkedInventory set!"));
	}

	if (LinkedInventory)
	{
		LinkedInventory->GetOnSlotFocusUpdated().AddUObject(this, &UInventorySlot::PlayerFocusChanged);
		LinkedInventory->GetOnInventoryUpdated().AddUObject(this, &UInventorySlot::PlayerInventoryChanged);

		const int32 FocusedSlot = LinkedInventory->GetCurrentFocusedSlot();
		PlayerFocusChanged(FocusedSlot);

		LinkedInventoryItem = LinkedInventory->GetItemBySlot(BagID, InventorySlot);
		BuildSlotVisuals();
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
	InventoryFunctions::SwapSlots(GetSlotRef(), Operation->OutgoingSlot);

	return true;
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
		LinkedInventoryItem = LinkedInventory->GetItemBySlot(BagID, InventorySlot);
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
				DragOp->OutgoingSlot = GetSlotRef();

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

FReply UInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!SlotChordLookup.Get({ InMouseEvent.GetEffectingButton() }))
	{
		const FReply DragReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, ClickAndDragKey).NativeReply;

		if (DragReply.IsEventHandled())
		{
			return DragReply;
		}
	}

	return FReply::Unhandled();
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

void UInventorySlot::QuickTransfer()
{
	if (UUISettings* UISettings = UUISettings::Get())
	{
		if (UObject* TransferRequestLookup = UISettings->TransferRequestTargetAsset.TryLoad())
		{
			TransferRequest::RequestTransfer(GetSlotRef(), SlotDomain, *TransferRequestLookup);
		}
	}
}

