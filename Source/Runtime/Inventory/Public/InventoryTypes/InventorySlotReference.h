#pragma once

class CompoundInventory;

/**
 * Wrapper class for UInventorySlots and what they actually represent under the hood.
 */

class INVENTORY_API InventorySlotReference
{
public:

	InventorySlotReference() {};

	InventorySlotReference(CompoundInventory* InAssociatedInventory, const FGuid& InBagRef, const uint32 InSlotNum)
		: AssociatedInventory(InAssociatedInventory)
		, BagReference(InBagRef)
		, SlotNumberReference(InSlotNum)
	{}

	CompoundInventory* AssociatedInventory;

	FGuid BagReference;
	int32 SlotNumberReference;
};