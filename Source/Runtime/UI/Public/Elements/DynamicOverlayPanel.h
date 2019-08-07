// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/Elements/OverlayLockInterface.h"

#include <Runtime/UMG/Public/Components/Overlay.h>

#include "DynamicOverlayPanel.generated.h"

UCLASS(meta = (DisplayName = "DynamicOverlayPanel"))
class UDynamicOverlayPanel : public UOverlay
{
	GENERATED_BODY()

	UDynamicOverlayPanel();

public:

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;;
#endif //WITH_EDITOR
	
	bool GetIsLocked() const
	{
		return LockingInterface != nullptr;
	};

protected:

	virtual void OnSlotAdded(UPanelSlot* InSlot) override;
	virtual void OnSlotRemoved(UPanelSlot* InSlot) override;

private:

	UPROPERTY()
	TScriptInterface<IOverlayLockInterface> LockingInterface;
};
