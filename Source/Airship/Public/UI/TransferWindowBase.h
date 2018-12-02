// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/AirWidget.h"
#include "AirInventory.h"
#include "SequentialGridPanel.h"
#include "InventorySlot.h"
#include "TransferWindowBase.generated.h"

//////////////////////////////////////////////////////////////////////////
// Base for all Transfer windows.  These are inventory screens that can display 2 DIFFERENT inventories, and allow for transfer between them
//////////////////////////////////////////////////////////////////////////

UCLASS()
class AIRSHIP_API UTransferWindowBase : public UAirWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = Grids)
	USequentialGridPanel* OwnerPanel;

	UPROPERTY(BlueprintReadWrite, Category = Grids)
	USequentialGridPanel* PlayerPanel;

	UPROPERTY(BlueprintReadWrite, Category = Inventory)
	TSubclassOf<UInventorySlot> InventorySlotClass;

	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	UAirInventory* OwnerInventory;

	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	UAirInventory* PlayerInventory;

	UFUNCTION(BlueprintPure, Category = Inventory)
	UAirInventory* GetOwnerInventory() const { return OwnerInventory; }

	UFUNCTION(BlueprintPure, Category = Inventory)
	UAirInventory* GetPlayerInventory() const { return PlayerInventory; }

	void SetAppropriateInventories(UAirInventory* InOwnerInventory, UAirInventory* InPlayerInventory);
};
