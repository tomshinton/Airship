// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/AirWidget.h"

#include "TransferWindowBase.generated.h"

class UInventoryPanel;

//////////////////////////////////////////////////////////////////////////
// Base for all Transfer windows.  These are inventory screens that can display 2 DIFFERENT inventories, and allow for transfer between them
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI, abstract)
class UTransferWindowBase : public UAirWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = Grids, meta = (BindWidget))
	UInventoryPanel* OwnerPanel;

	UPROPERTY(EditDefaultsOnly, Category = Grids, meta = (BindWidget))
	UInventoryPanel* PlayerPanel;

	virtual void SynchronizeProperties() override;

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 Slots;

private:

	UPROPERTY()
	UAirInventory* OwnerInventory;

	UPROPERTY()
	UAirInventory* PlayerInventory;
};
