#pragma once

#include "Runtime/Inventory/Public/InventoryTypes/CompoundInventory.h"

DEFINE_LOG_CATEGORY_STATIC(CompoundInventoryLog, Log, Log);

CompoundInventory::CompoundInventory() 
	: Bags()
	, MaxBags(0)
{}

CompoundInventory::CompoundInventory(const TArray<FInventoryBag>& InDefaultBags, const int32 InMaxBags) 
	: Bags(InDefaultBags)
	, MaxBags(InMaxBags)
{
#if !UE_BUILD_SHIPPING
	checkf(Bags.Num() <= MaxBags, TEXT("CompoundInventory has more bags than MaxBags allows"));
#endif //!UE_BUILD_SHIPPING
}

CompoundInventory::~CompoundInventory()
{
	UE_LOG(CompoundInventoryLog, Log, TEXT("Compound Inventory Destroyed"));
}

void CompoundInventory::AddBag(const FInventoryBag& InNewBag)
{
	if (Bags.Num() < MaxBags)
	{
		Bags.Add(InNewBag);
	}
}

bool CompoundInventory::GetBag(const int32 InBagNum, FInventoryBag& OutBag) const
{
	if (Bags.IsValidIndex(InBagNum))
	{
		OutBag = Bags[InBagNum];
		return true;
	}

	return false;
}

FInventoryBag* CompoundInventory::GetBag(const FGuid& InBagID) const
{
	const FInventoryBag* FoundBag = Bags.FindByPredicate([InBagID](const FInventoryBag& Bag)
	{
		return Bag.GetBagID() == InBagID;
	});

	if (FoundBag != nullptr)
	{
		return const_cast<FInventoryBag*>(FoundBag);
	}

	return nullptr;
}

const FInventoryBag* CompoundInventory::GetBagByType(const EBagType& InType) const
{
	return Bags.FindByPredicate([InType](const FInventoryBag& Bag)
	{
		return Bag.GetBagType() == InType;
	});

	return nullptr;
}

void CompoundInventory::GetSlotByID(const FGuid& InBagID, const FGuid& InSlotID, FInventoryItem& OutSlot)
{
	for (const FInventoryBag& Bag : Bags)
	{
		if (Bag.GetBagID() == InBagID)
		{
			for (const FInventoryItem& Slot : Bag.BagSlots)
			{
				if (Slot.GetSlotID() == InSlotID)
				{
					OutSlot = Slot;
				}
			}
		}
	}
}

