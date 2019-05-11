// Airship Project - Tom Shinton 2018

#pragma once

#include "AirWidget.h"
#include "SequentialGridPanel.h"
#include <GridPanel.h>
#include "InventorySlot.h"
#include "InventoryPanel.generated.h"

UCLASS()
class AIRUI_API UInventoryPanel : public UAirWidget
{
	GENERATED_BODY()
	
public:

	UInventoryPanel(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	UGridPanel* PanelBody;

	UPROPERTY(EditAnywhere, Category = "Slots")
	int32 Columns;
	
	UPROPERTY(EditAnywhere, Category = "Slots")
	TSubclassOf<UInventorySlot> SlotClass;

protected:

	virtual void NativeConstruct() override;
};
