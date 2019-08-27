// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/AirWidget.h"
#include "Runtime/UI/Public/Actions/DraggableInterface.h"

#include "Runtime/UI/Public/Widgets/Inventory/InventoryViewInterface.h"
#include "Widget.h"
#include "InventoryPanel.generated.h"

class UGridPanel;
class UGridSlot;
class USizeBox;
class UTextBlock;

UCLASS()
class UI_API UInventoryPanel : public UAirWidget
	, public IInventoryViewInterface
	, public IDraggableInterface
{
	GENERATED_BODY()
	
public:

	UInventoryPanel(const FObjectInitializer& ObjectInitializer);

	virtual void Build() override;

	virtual void SynchronizeProperties() override;

	// InventoryViewInterface
	virtual void SetLinkedInventory(IInventoryInterface* InInterface) override
	{
		LinkedInventory.SetInterface(InInterface);
		LinkedInventory.SetObject(this);
	};
	virtual void SetLinkedHotbar(IHotbarInterface* InInterface) override {};
	virtual void SetSlotDomain(const ESlotDomain InDomain) override { SlotDomain = InDomain; };
	//~InventoryViewInterface

	// DraggableInterface
	virtual FDraggableHandle GetDraggableHandle() override { return FDraggableHandle(this, (UWidget*)MoveHandle); };
	//~DraggableInterface

	UPROPERTY(meta = (BindWidget))
	UGridPanel* PanelBody;
	
	UPROPERTY(meta = (BindWidget))
	USizeBox* MoveHandle;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HandleNameBlock;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 Columns;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 Slots;
	
	UPROPERTY(EditAnywhere, Category = "Handle")
	bool ShowMoveHandle;

	UPROPERTY(EditAnywhere, Category = "Handle")
	FText InventoryName;

	UPROPERTY(EditAnywhere, Category = "Slots")
	ESlotDomain SlotDomain;

private:

	UPROPERTY()
	TScriptInterface<IInventoryInterface> LinkedInventory;

	bool IsMoving;

	FKey ClickAndDragKey;

	FVector2D MouseDragDelta;

	FVector2D MousePosition;
};
