// Airship Project - Tom Shinton 2018

#include "Runtime/UI/Public/QuickTransfer/Targets/TransferTargetPlayerBackpack.h"

#include <Runtime/Inventory/Public/InventoryFunctions.h>

TOptional<InventorySlotReference> UTransferTargetPlayerBackpack::GetTarget(const InventorySlotReference& InReference)
{
	//Get me any other bag that's NOT the hotbar
	return InventoryFunctions::GetFirstSlotNotOfType(*InReference.AssociatedInventory, EBagType::Hotbar);
}
