// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/AirWidget.h"

#include <AirCore\Public\Interfaces\InteractableInterface.h>
#include <AirCore\Public\Interfaces\InteractionInterface.h>

#include "InspectorPanel.generated.h"

class UTextBlock;

//////////////////////////////////////////////////////////////////////////
// Base class for Inspection - What am i looking at, and how do i interact with it?
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI)
class UInspectorPanel : public UAirWidget
{
	GENERATED_BODY()

public:

	UInspectorPanel(const FObjectInitializer& ObjectInitializer);

	void SetInteractionInterface(IInteractionInterface* InInteractionInterface);

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DisplayNameBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractionKeyBlock;
	
	UPROPERTY(meta = (BindWidgetAnim))
	UWidgetAnimation* ShowAnim;

	UPROPERTY(meta = (BindWidgetAnim))
	UWidgetAnimation* HideAnim;

	TScriptInterface<IInteractionInterface> InteractionInterface;

	void ShowPanel(const IInteractableInterface& InteractableInterface);
	void HidePanel();

	FText GetInteractionKeyString() const;

protected:

	virtual void NativeConstruct() override;

private:

	UFUNCTION()
	void OnHidePanelOver();
};
