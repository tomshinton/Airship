// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AirWidget.h"
#include "AirInventory.h"
#include "Utils/Datatypes/InventoryItems.h"
#include "InventorySlot.generated.h"

class UInventorySlotPayload;
class UTextBlock;
class UImage;
class UDragAndDropVisual;

UCLASS()
class UInventorySlot : public UAirWidget
{
	GENERATED_BODY()

public:

	//Elements
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ClipText;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuantityText;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Inventory)
	void UpdateFocused();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Inventory)
	void UpdateFocusCleared();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Inventory)
	void UpdateSlotVisuals();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Inventory)
	FInventoryItem GetLinkedItem();

	UFUNCTION(BlueprintCallable, Category = DragAndDrop)
	bool OnInventorySlotDrop(UInventorySlotDragOperation* Payload);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void SetInventorySlot(const int32 InSlot, bool InIsHotbarSlot);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	UAirInventory* GetLinkedInventory() const { return LinkedInventory.Get(); }

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void SetLinkedInventory(UAirInventory* InInventory) { LinkedInventory = InInventory; };

	UPROPERTY(EditAnywhere, Category = Inventory)
	int32 InventorySlot;

	UPROPERTY(EditAnywhere, Category = Inventory)
	bool IsHotBarSlot;
	
	virtual void Build() override;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	bool IsPopulated;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = DragAndDrop)
	TSubclassOf<UDragAndDropVisual> DragAndDropVisual;

	UFUNCTION()
	void PlayerFocusChanged(int32 InSlot);

	UFUNCTION()
	void PlayerInventoryChanged();

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

private:
	
	bool IsFocused;

	void BuildSlotVisuals();

	void BuildFromValidData(FInventoryItemRow* Row);

	void BuildFromInvalidData();

	FInventoryItem LinkedInventoryItem;
	UPROPERTY()
	TWeakObjectPtr<UAirInventory> LinkedInventory;
};
