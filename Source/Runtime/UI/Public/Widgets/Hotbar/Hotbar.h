// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/AirWidget.h"
#include "Runtime/UI/Public/Widgets/Inventory/InventoryViewInterface.h"

#include <Runtime/Inventory/Public/HotbarInterface.h>
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

	virtual void Build() override;

	//IInventoryViewInterface
	virtual void SetLinkedInventory(IInventoryInterface* InInterface) override
	{
		LinkedInventory.SetInterface(InInterface);
		LinkedInventory.SetObject(this);
	};

	virtual void SetLinkedHotbar(IHotbarInterface* InInterface) override 
	{ 
		LinkedHotbar.SetInterface(InInterface);
		LinkedHotbar.SetObject(this);
	};
	//~IInventoryViewInterface

private:

	void SetHotbarSlotCount();

	int32 HotbarSlotCount;

	TScriptInterface<IInventoryViewInterface> LinkedInventory;
	TScriptInterface<IHotbarInterface> LinkedHotbar;
};
