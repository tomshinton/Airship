// Airship Project - Tom Shinton 2018

#include "Runtime/UI/Public/Elements/DynamicOverlayPanel.h"

#include <Runtime/UMG/Public/Components/PanelSlot.h>

UDynamicOverlayPanel::UDynamicOverlayPanel()
	: LockingInterface(nullptr)
{}

#define LOCTEXT_NAMESPACE "UMG"
const FText UDynamicOverlayPanel::GetPaletteCategory()
{
	return LOCTEXT("", "Common");
}

void UDynamicOverlayPanel::OnSlotAdded(UPanelSlot* InSlot)
{
	Super::OnSlotAdded(InSlot);

	if (UWidget* SlotContent = InSlot->Content)
	{
		if (IOverlayLockInterface* LockInterface = Cast<IOverlayLockInterface>(SlotContent))
		{
			if (LockInterface->ShouldLockOverlay())
			{
				LockingInterface.SetInterface(LockInterface);
				LockingInterface.SetObject(SlotContent);
			}
		}
	}
}

void UDynamicOverlayPanel::OnSlotRemoved(UPanelSlot* InSlot)
{
	Super::OnSlotRemoved(InSlot);

	if (!LockingInterface)
	{
		return;
	}
	else
	{
		if (UWidget* SlotContent = InSlot->Content)
		{
			if (IOverlayLockInterface* LockInterface = Cast<IOverlayLockInterface>(SlotContent))
			{
				LockingInterface = NULL;
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
