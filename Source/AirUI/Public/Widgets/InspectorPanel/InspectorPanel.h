// Airship Project - Tom Shinton 2018

#pragma once

#include "CoreMinimal.h"
#include "AirWidget.h"
#include "InteractableInterface.h"
#include "InteractionInterface.h"
#include "InspectorPanel.generated.h"

class UTextBlock;

//////////////////////////////////////////////////////////////////////////
// Base class for Inspection - What am i looking at, and how do i interact with it?
//////////////////////////////////////////////////////////////////////////

UCLASS()
class AIRUI_API UInspectorPanel : public UAirWidget
{
	GENERATED_BODY()

public:

	UInspectorPanel(const FObjectInitializer& ObjectInitializer);

	void SetInteractionInterface(IInteractionInterface* InInteractionInterface);

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DisplayNameBlock;

	TScriptInterface<IInteractionInterface> InteractionInterface;

	void OnNewItemLookedAt(const FText& InItemDisplayName);

	void ShowPanel();
	void HidePanel();

protected:

	virtual void NativeDestruct() override;
};
