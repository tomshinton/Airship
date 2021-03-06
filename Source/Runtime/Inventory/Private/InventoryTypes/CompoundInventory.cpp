// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/Inventory/Public/InventoryTypes/CompoundInventory.h"

DEFINE_LOG_CATEGORY_STATIC(CompoundInventoryLog, Log, Log);

CompoundInventory::CompoundInventory() 
	: Bags()
	, MaxBags(0)
{}

CompoundInventory::CompoundInventory(const TArray<FInventoryBag>& InDefaultBags, const int32 InMaxBags, const TFunction<void()>& InUpdateFunc)
	: Bags(InDefaultBags)
	, MaxBags(InMaxBags)
	, UpdateFunc(InUpdateFunc)
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
		FInventoryBag PreInitBag = InNewBag;
		PreInitBag.InitSlots();

#if !UE_BUILD_SHIPPING
		checkf(PreInitBag.BagSlots.Num() > 0, TEXT("Could not init BagSlots!"));
#endif //!UE_BUILD_SHIPPING

		UE_LOG(CompoundInventoryLog, Log, TEXT("Adding bag %s, with %i slots"), *PreInitBag.BagName, PreInitBag.SlotsNum);
		Bags.Add(PreInitBag);
	}

	UpdateFunc();
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

void CompoundInventory::Clear()
{
	Bags.Empty();
	UpdateFunc();
}

