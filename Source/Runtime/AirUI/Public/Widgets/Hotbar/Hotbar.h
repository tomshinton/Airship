// Airship Project - Tom Shinton 2018

#pragma once

class UInventorySlot;
class UHorizontalBox;

#include "AirWidget.h"
#include "AirInventory.h"
#include "InventoryViewInterface.h"
#include "Hotbar.generated.h"

UCLASS()
class AIRUI_API UHotbar : public UAirWidget
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
