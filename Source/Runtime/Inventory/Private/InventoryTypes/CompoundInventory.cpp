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

TArray<FInventoryItem> CompoundInventory::GetAllSlots() const
{
	TArray<FInventoryItem> RunningTotal;
	for (const FInventoryBag& Bag : Bags)
	{
		RunningTotal.Append(Bag.GetSlots());
	}

	return RunningTotal;
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

bool CompoundInventory::GetBag(const FGuid& InBagID, FInventoryBag& OutBag) const
{
	const FInventoryBag* FoundBag = Bags.FindByPredicate([InBagID](const FInventoryBag& Bag)
	{
		return Bag.GetBagID() == InBagID;
	});

	if (FoundBag != nullptr)
	{
		OutBag = *FoundBag;
		return true;
	}

	return false;
}

const FInventoryBag* CompoundInventory::GetBagByType(const EBagType& InType) const
{
	return Bags.FindByPredicate([InType](const FInventoryBag& Bag)
	{
		return Bag.GetBagType() == InType;
	});

	return nullptr;
}

