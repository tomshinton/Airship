// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/AirWidget.h"
#include "Runtime/UI/Public/Widgets/Inventory/InventoryViewInterface.h"
 
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

	UPROPERTY(VisibleAnywhere, Category = "Slots")
	TSubclassOf<UInventorySlot> SlotClass;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 SlotsToAdd;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox*	Bar;

	UPROPERTY(EditAnywhere, Category = "Slots")
	ESlotDomain SlotDomain;

	virtual void SynchronizeProperties() override;

	virtual void Build() override;

	//IInventoryViewInterface
	virtual void SetLinkedInventory(IInventoryInterface* InInterface, const FGuid& InBagID) override
	{
		LinkedInventory.SetInterface(InInterface);
		LinkedInventory.SetObject(this);
	
		BagID = InBagID;
	};
	virtual void SetSlotDomain(const ESlotDomain InDomain) override { SlotDomain = InDomain; };
	//~IInventoryViewInterface

private:

	int32 HotbarSlotCount;

	TScriptInterface<IInventoryInterface> LinkedInventory;
	FGuid BagID;
};
