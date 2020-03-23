// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/QuickTransfer/BagFinder/BagFinder.h"

#include <Runtime/Inventory/Public/InventoryTypes/InventoryBagReference.h>

TArray<InventoryBagReference> BagFinder::Get() const
{
	TArray<InventorySlotReference> FoundSlots = InvSlotFinder.Get();
	TArray<InventoryBagReference> FoundBags;

	if (FoundSlots.Num() > 0)
	{
		for (const InventorySlotReference& Slot : FoundSlots)
		{
			bool BagAlreadyFound = false;

			for (const InventoryBagReference& Bag : FoundBags)
			{
				if (Bag.BagReference == Slot.BagReference)
				{
					BagAlreadyFound = true;
					break;
				}
			}

			if (!BagAlreadyFound)
			{
				FoundBags.Add(InventoryBagReference(/*Slot.AssociatedInventory, Slot.BagReference*/));
			}
		}
	}

#if !UE_BUILD_SHIPPING
	UE_LOG(InvBagFinderLog, Warning, TEXT("No bags found on screen that match the supplied filters"))
#endif //!UE_BUILD_SHIPPING

	return FoundBags;
}
