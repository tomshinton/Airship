// Airship Project - Tom Shinton 2018

#pragma once

#include "AirWidget.h"
#include "SequentialGridPanel.h"
#include <GridPanel.h>
#include "InventorySlot.h"
#include "InventoryViewInterface.h"

#include "InventoryPanel.generated.h"

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
	
	virtual void SynchronizeProperties() override;

	// InventoryViewInterface
	virtual void SetLinkedInventory(IInventoryInterface* InInterface) override
	{
		LinkedInventory.SetInterface(InInterface);
		LinkedInventory.SetObject(this);
	};
	virtual void SetLinkedHotbar(IHotbarInterface* InInterface) {};
	//~InventoryViewInterface

private:

	UPROPERTY()
	TScriptInterface<IInventoryInterface> LinkedInventory;
};
