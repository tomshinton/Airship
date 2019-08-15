// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/AirWidget.h"
#include "Runtime/UI/Public/Widgets/Inventory/InventoryViewInterface.h"

#include "InventoryPanel.generated.h"

class UGridPanel;
class UGridSlot;

UCLASS()
class UI_API UInventoryPanel : public UAirWidget
	, public IInventoryViewInterface
{
	GENERATED_BODY()
	
public:

	virtual void Build() override;

public:

	UInventoryPanel(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	UGridPanel* PanelBody;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 Columns;

	int32 DynamicColumns;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 Slots;
	
	UPROPERTY(EditAnywhere, Category = "Slots")
	ESlotDomain SlotDomain;

	virtual void SynchronizeProperties() override;

	// InventoryViewInterface
	virtual void SetLinkedInventory(IInventoryInterface* InInterface) override
	{
		LinkedInventory.SetInterface(InInterface);
		LinkedInventory.SetObject(this);
	};
	virtual void SetLinkedHotbar(IHotbarInterface* InInterface) override {};
	virtual void SetSlotDomain(const ESlotDomain InDomain) override { SlotDomain = InDomain; };
	//~InventoryViewInterface

private:

	UPROPERTY()
	TScriptInterface<IInventoryInterface> LinkedInventory;
};
