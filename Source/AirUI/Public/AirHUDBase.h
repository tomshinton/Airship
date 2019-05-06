// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AirWidget.h"
#include "AirHUDBase.generated.h"

class UCanvasPanel;
class UHotbar;

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
	
protected:
};
