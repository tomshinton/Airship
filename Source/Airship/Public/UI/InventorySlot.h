// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/AirWidget.h"
#include "AirInventory.h"
#include "Utils/Datatypes/InventoryItems.h"
#include "InventorySlot.generated.h"

class UInventorySlotPayload;

UCLASS()
class AIRSHIP_API UInventorySlot : public UAirWidget
{
	GENERATED_BODY()

public:

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
	void SetInventorySlot(const int32 InSlot, bool InIsHotbarSlot) { InventorySlot = InSlot; IsHotBarSlot = InIsHotbarSlot; };

	UFUNCTION(BlueprintCallable, Category = Inventory)
	UAirInventory* GetLinkedInventory() const { return LinkedInventory.Get(); }

	UPROPERTY(EditAnywhere, Category = Inventory)
	int32 InventorySlot;

	UPROPERTY(EditAnywhere, Category = Inventory)
	bool IsHotBarSlot;
	
	virtual void Build() override;

protected:
	
	UFUNCTION()
	void PlayerFocusChanged(int32 InSlot);

	UFUNCTION()
	void PlayerInventoryChanged();

private:
	bool IsFocused;

	FInventoryItem LinkedInventoryItem;
	UPROPERTY()
	TWeakObjectPtr<UAirInventory> LinkedInventory;
};
