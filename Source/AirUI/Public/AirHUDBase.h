// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AirWidget.h"
#include "AirHUDBase.generated.h"

class UCanvasPanel;
class UHotbar;
class UInventoryPanel;
class UHealthbar;

//////////////////////////////////////////////////////////////////////////
// Base for AirHud, the main Hud of the game.  Holds containers for all contextual widgets like ActiveInventory and Hotbars
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI)
class UAirHUDBase : public UAirWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = Composite, meta = (BindWidget))
	UHotbar* Hotbar;

	UPROPERTY(EditDefaultsOnly, Category = Composite, meta = (BindWidget))
	UInventoryPanel* PlayerInventoryPanel;

	UPROPERTY(EditDefaultsOnly, Category = Composite, meta = (BindWidget))
	UHealthbar* PlayerHealthBar;

	AIRUI_API void SetupBinding(UInputComponent* InInputComponent);

protected:

	virtual void NativeConstruct() override;

private:

	void ToggleInventoryPanel();
};
