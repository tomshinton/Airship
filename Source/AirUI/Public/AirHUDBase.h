// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AirWidget.h"
#include "AirHUDBase.generated.h"

class UCanvasPanel;
class UHotbar;
class UInventoryPanel;
class UHealthbar;
class UInspectorPanel;
class UOverlay;

//////////////////////////////////////////////////////////////////////////
// Base for AirHud, the main Hud of the game.  Holds containers for all contextual widgets like ActiveInventory and Hotbars
//////////////////////////////////////////////////////////////////////////

UCLASS(abstract, MinimalAPI)
class UAirHUDBase : public UAirWidget
{
	GENERATED_BODY()

public:

	UAirHUDBase(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, Category = Composite, meta = (BindWidget))
	UHotbar* Hotbar;

	UPROPERTY(EditDefaultsOnly, Category = Composite, meta = (BindWidget))
	UInventoryPanel* PlayerInventoryPanel;

	UPROPERTY(EditDefaultsOnly, Category = Composite, meta = (BindWidget))
	UHealthbar* PlayerHealthBar;

	UPROPERTY(EditDefaultsOnly, Category = Composite, meta = (BindWidget))
	UInspectorPanel* InspectorPanel;

	UPROPERTY(EditDefaultsOnly, Category = Composite, meta = (BindWidget))
	UOverlay* DynamicOverlay;

	AIRUI_API void SetupBinding(UInputComponent* InInputComponent);

	void OnDynamicPanelUpdated();
	 
protected:

	virtual void NativeConstruct() override;

private:

	static bool ShouldBeSnapshot(UWidget* InWidget, UWidgetTree* InWidgetTree, UOverlay* InOverlay);

	void ToggleInventoryPanel();

	void TakeSnapshot();
	void RestoreSnapshot();

	bool TryRemoveTopLevelDynamicWidget();

	TMap<UWidget*, ESlateVisibility> Snapshot;
};
