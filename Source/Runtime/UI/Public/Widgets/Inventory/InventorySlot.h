// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AirWidget.h"
#include "AirInventory.h"
#include "InventoryViewInterface.h"
#include "InventorySlot.generated.h"

struct FInventoryItem;

class UInventorySlotPayload;
class UTextBlock;
class UImage;
class UDragAndDropVisual;
class USizeBox;

UCLASS(abstract)
class UInventorySlot : public UAirWidget
	, public IInventoryViewInterface
{
	GENERATED_BODY()

public:

	static const FName Anim_Focus;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SlotBody;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ClipText;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuantityText;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Inventory)
	FInventoryItem GetLinkedItem();

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

	UPROPERTY(EditANywhere, Category = DragAndDrop)
	TSubclassOf<UDragAndDropVisual> DragAndDropVisual;

	virtual void SynchronizeProperties() override;
	
	// InventoryViewInterface
	virtual void SetLinkedInventory(UAirInventory* InAirInventory) override { LinkedInventory = InAirInventory; };
	//~InventoryViewInterface

protected:

	UFUNCTION()
	void PlayerFocusChanged(int32 InSlot);

	UFUNCTION()
	void PlayerInventoryChanged();

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeConstruct() override;

private:
	
	UPROPERTY()
	UAirInventory* LinkedInventory;

	bool IsFocused;

	void BuildSlotVisuals();

	void BuildFromValidData(FInventoryItemRow* Row);

	void BuildFromInvalidData();

	FInventoryItem LinkedInventoryItem;
};
