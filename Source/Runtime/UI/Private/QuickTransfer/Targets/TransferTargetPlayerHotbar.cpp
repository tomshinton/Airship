// Airship Project - Tom Shinton 2018

#include "Runtime/UI/Public/QuickTransfer/Targets/TransferTargetPlayerHotbar.h"

#include <Runtime/Inventory/Public/InventoryFunctions.h>

TOptional<InventorySlotReference> UTransferTargetPlayerHotbar::GetTarget(const InventorySlotReference& InReference)
{
	return InventoryFunctions::GetFirstSlotOfType(*InReference.AssociatedInventory, EBagType::Hotbar);
}
