// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/AirWidget.h"
#include "Runtime/UI/Public/Widgets/Inventory/InventoryViewInterface.h"

#include <Runtime/Input/Public/Types/ChordLookup.h>
#include <Runtime/Inventory/Public/InventoryComponent/AirInventory.h>
#include <Runtime/Inventory/Public/InventoryTypes/InventoryItem.h>

#include "InventorySlot.generated.h"

class UInventorySlotPayload;
class UTextBlock;
class UImage;
class UDragAndDropVisual;
class USizeBox;

class InventorySlotReference;

DECLARE_LOG_CATEGORY_EXTERN(InventorySlotLog, All, All);

UCLASS(abstract)
class UInventorySlot : public UAirWidget
	, public IInventoryViewInterface
{
	GENERATED_BODY()

	friend class InventorySlotReference;

public:

	UInventorySlot(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	USizeBox* SlotBody;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ClipText;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuantityText;

	UPROPERTY(meta = (BindWidgetAnim))
	UWidgetAnimation* FocusAnim;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Inventory)
	FInventoryItem GetLinkedItem();

	virtual void Build() override;

	UFUNCTION(BlueprintCallable, Category = DragAndDrop)
	bool OnInventorySlotDrop(UInventorySlotDragOperation* Payload);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void SetInventorySlot(const int32 InSlot, bool InIsHotbarSlot);

	UPROPERTY(EditAnywhere, Category = Inventory)
	int32 InventorySlot;

	UPROPERTY(EditAnywhere, Category = Inventory) 
	bool IsHotBarSlot;
	
	UPROPERTY(VisibleAnywhere, Category = Inventory)
	bool IsPopulated;

	UPROPERTY(EditAnywhere, Category = DragAndDrop)
	TSubclassOf<UDragAndDropVisual> DragAndDropVisual;

	virtual void SynchronizeProperties() override;
	
	// InventoryViewInterface
	virtual void SetLinkedInventory(IInventoryInterface* InInterface, const FGuid& InBagID) override
	{
		LinkedInventory.SetInterface(InInterface);
		LinkedInventory.SetObject(this);

		BagID = InBagID;
	};
	virtual void SetSlotDomain(const ESlotDomain InDomain) override { SlotDomain = InDomain; };
	//~InventoryViewInterface

	InventorySlotReference GetSlotRef();

protected:

	UPROPERTY(VisibleAnywhere, Category = DragAndDrop)
	ESlotDomain SlotDomain;

	UFUNCTION()
	void PlayerFocusChanged(int32 InSlot);

	UFUNCTION()
	void PlayerInventoryChanged();

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	
	TScriptInterface<IInventoryInterface> LinkedInventory;
	
	bool IsFocused;

	FKey ClickAndDragKey;

	void BuildSlotVisuals();

	void BuildFromValidData(FInventoryItemRow* Row);

	void BuildFromInvalidData();

	FInventoryItem LinkedInventoryItem;

	ChordLookup SlotChordLookup;

	void QuickTransfer();

	FGuid BagID;
};
