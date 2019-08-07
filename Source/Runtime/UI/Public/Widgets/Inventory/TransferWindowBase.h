// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/AirWidget.h"
#include "Runtime/UI/Public/Elements/OverlayLockInterface.h"

#include <Runtime/Inventory/Public/InventoryInterface.h>

#include "TransferWindowBase.generated.h"

class UInventoryPanel;

//////////////////////////////////////////////////////////////////////////
// Base for all Transfer windows.  These are inventory screens that can display 2 DIFFERENT inventories, and allow for transfer between them
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI, abstract, hidedropdown)
class UTransferWindowBase : public UAirWidget
	, public IOverlayLockInterface
{
	GENERATED_BODY()

public:

	UI_API static UTransferWindowBase* NewWindow(IInventoryInterface& OwningInterface, IInventoryInterface& PlayerInterface, UWorld& WorldContext);

	UPROPERTY(EditDefaultsOnly, Category = Grids, meta = (BindWidget))
	UInventoryPanel* OwnerPanel;

	UPROPERTY(EditDefaultsOnly, Category = Grids, meta = (BindWidget))
	UInventoryPanel* PlayerPanel;

	virtual void SynchronizeProperties() override;

	virtual void Build() override;

	void SetOwningInventory(IInventoryInterface* OwningInterface);
	void SetPlayerInventory(IInventoryInterface* PlayerInterface);

	//OverlayLockInterface
	virtual bool ShouldLockOverlay() const override;
	//~OverlayLockInterface

protected:

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 Slots;

private:

	TScriptInterface<IInventoryInterface> OwnerInventory;
	TScriptInterface<IInventoryInterface> PlayerInventory;
};
