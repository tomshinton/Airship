// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AirWidget.h"
#include "AirHUDBase.generated.h"

class UCanvasPanel;

//////////////////////////////////////////////////////////////////////////
// Base for AirHud, the main Hud of the game.  Holds containers for all contextual widgets like ActiveInventory and Hotbars
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI)
class UAirHUDBase : public UAirWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Containers")
	void SetInventoryPanel(UCanvasPanel* InPanel) { InventoryPanel = InPanel; };
	AIRUI_API void AddInventoryWidgetToPanel(UUserWidget* InWidget);
	AIRUI_API void RemoveInventoryWidgetFromPanel();
	AIRUI_API bool IsInventoryPanelPopulated() const;
	void SetInventoryPanelVisiblity(const ESlateVisibility InNewVisibility);

	virtual void Build() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = Containers)
	UCanvasPanel* InventoryPanel;

	UPROPERTY(EditDefaultsOnly, Category = Containers)
	UCanvasPanel* ClipPanel;
};
