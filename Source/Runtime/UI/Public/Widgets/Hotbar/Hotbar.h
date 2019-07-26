// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/AirWidget.h"
#include "Runtime/UI/Public/Widgets/Inventory/InventoryViewInterface.h"

#include <Runtime/Inventory/Public/InventoryComponent/AirInventory.h>

#include "Hotbar.generated.h"

class UInventorySlot;
class UHorizontalBox;

UCLASS()
class UI_API UHotbar : public UAirWidget
	, public IInventoryViewInterface
{
	GENERATED_BODY()
	
public:

	UHotbar(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = "Slots")
	TSubclassOf<UInventorySlot> SlotClass;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 SlotsToAdd;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox*	Bar;

	virtual void SynchronizeProperties() override;

	//IInventoryViewInterface
	virtual void SetLinkedInventory(UAirInventory* InAirInventory) override { LinkedInventory = InAirInventory; };
	//~IInventoryViewInterface

protected:

	virtual void NativeConstruct() override;

private:

	void SetHotbarSlotCount();

	int32 HotbarSlotCount;

	UPROPERTY()
	UAirInventory* LinkedInventory;
};
