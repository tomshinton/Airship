// Airship Project - Tom Shinton 2018

#pragma once

class UAirHUDBase;
class UTransferWindowBase;
class UInventorySlot;

#include "UISettings.generated.h"

///////////////////////////////////////////////////////////////////////////
// GameSettings asset for global assets - accessed via UnmutableDefaults
//////////////////////////////////////////////////////////////////////////

UCLASS(config = Game, defaultconfig, MinimalAPI)
class UUISettings : public UObject
{
	GENERATED_BODY()

public:

	static UUISettings* Get()
	{
		return GetMutableDefault<UUISettings>();
	}

	UPROPERTY(EditAnywhere, config, Category = "UI | HUD")
	TSubclassOf<UAirHUDBase> HUDWidgetClass;

	UPROPERTY(EditAnywhere, config, Category = "UI | Inventory")
	TSubclassOf<UTransferWindowBase> TransferWindowClass;

	UPROPERTY(EditAnywhere, config, Category = "UI | Inventory")
	TSubclassOf<UInventorySlot> InventorySlotClass;

	UPROPERTY(EditAnywhere, config, Category = "UI | Inventory")
	float InventorySlotSize;
};
