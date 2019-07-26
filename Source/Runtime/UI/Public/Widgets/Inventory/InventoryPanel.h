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

	static const FName Anim_Show;

public:

	UInventoryPanel(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	UGridPanel* PanelBody;

	UPROPERTY(EditAnywhere, Category = "Slots")
	bool UseDynamicRows;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 Columns;

	int32 DynamicColumns;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 Slots;
	
	virtual void SynchronizeProperties() override;

	// InventoryViewInterface
	virtual void SetLinkedInventory(UAirInventory* InAirInventory) override { LinkedInventory = InAirInventory; };
	//~InventoryViewInterface

protected:

	virtual void NativeConstruct() override;

	void SetDynamicColumns();

private:

	UPROPERTY()
	UAirInventory* LinkedInventory;
};
