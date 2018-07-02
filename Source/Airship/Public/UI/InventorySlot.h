// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/AirWidget.h"
#include "Datatypes/InventoryItems.h"
#include "AirInventory.h"
#include "InventorySlot.generated.h"

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

	UPROPERTY(EditAnywhere, Category = Inventory)
	int32 InventorySlot;
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void PlayerFocusChanged(int32 InSlot);

	UFUNCTION()
	void PlayerInventoryChanged();

private:
	bool IsFocused;

	FInventoryItem LinkedInventoryItem;
	UAirInventory* PlayerInventory;
};
