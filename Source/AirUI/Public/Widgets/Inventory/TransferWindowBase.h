// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AirWidget.h"
#include "AirInventory.h"
#include "SequentialGridPanel.h"
#include "InventorySlot.h"
#include "TransferWindowBase.generated.h"

//////////////////////////////////////////////////////////////////////////
// Base for all Transfer windows.  These are inventory screens that can display 2 DIFFERENT inventories, and allow for transfer between them
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI, abstract)
class UTransferWindowBase : public UAirWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = Grids, meta = (BindWidget))
	USequentialGridPanel* OwnerPanel;

	UPROPERTY(EditDefaultsOnly, Category = Grids, meta = (BindWidget))
	USequentialGridPanel* PlayerPanel;

	virtual void SynchronizeProperties() override;

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 Columns;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 Slots;

private:

	UPROPERTY()
	UAirInventory* OwnerInventory;

	UPROPERTY()
	UAirInventory* PlayerInventory;
};
