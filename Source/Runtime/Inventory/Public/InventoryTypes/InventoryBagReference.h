// Airship Project - Tom Shinton 2018

#pragma once

class CompoundInventory;

/**
 * Wrapper class for FInventoryBag* and what they actually represent under the hood.
 */

class INVENTORY_API InventoryBagReference
{

public:

	InventoryBagReference()
		: AssociatedInventory(nullptr)
		, BagReference()
	{};

	InventoryBagReference(CompoundInventory* InAssociatedInventory, const FGuid& InBagRef)
		: AssociatedInventory(InAssociatedInventory)
		, BagReference(InBagRef)
	{};

	UPROPERTY()
	CompoundInventory* AssociatedInventory;

	FGuid BagReference;
};