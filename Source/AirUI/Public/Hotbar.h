// Airship Project - Tom Shinton 2018

#pragma once

class UInventorySlot;
class UHorizontalBox;

#include "AirWidget.h"
#include "Hotbar.generated.h"

UCLASS()
class AIRUI_API UHotbar : public UAirWidget
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

protected:
	virtual void NativeConstruct() override;

private:

	void SetHotbarSlotCount();

	int32 HotbarSlotCount;
};
