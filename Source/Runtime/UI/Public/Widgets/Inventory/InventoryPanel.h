// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/AirWidget.h"
#include "Runtime/UI/Public/Widgets/Inventory/InventoryViewInterface.h"

#include "InventoryPanel.generated.h"

class UDraggableComponent;
class UGridPanel;
class UGridSlot;
class USizeBox;

UCLASS()
class UI_API UInventoryPanel : public UAirWidget
	, public IInventoryViewInterface
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

	UPROPERTY(meta = (BindWidget))
	UGridPanel* PanelBody;
	
	UPROPERTY(meta = (BindWidget))
	USizeBox* MoveHandle;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 Columns;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 Slots;
	
	UPROPERTY(EditAnywhere, Category = "Body")
	bool ShowMoveHandle;

	UPROPERTY(EditAnywhere, Category = "Slots")
	ESlotDomain SlotDomain;

protected:
	
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	UPROPERTY()
	TScriptInterface<IInventoryInterface> LinkedInventory;

	bool IsMoving;

	FKey ClickAndDragKey;

	FVector2D MouseDragDelta;

	FVector2D MousePosition;
};
