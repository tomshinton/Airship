// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/Inventory/Public/InventoryTypes/InventoryBag.h"

class CompoundInventory
{

public:

	CompoundInventory();
	~CompoundInventory();

	CompoundInventory(const TArray<FInventoryBag>& InDefaultBags, const int32 InMaxBags);
	   
	TArray<FInventoryItem> GetAllSlots() const;

	void AddBag(const FInventoryBag& InNewBag);

	bool GetBag(const int32 InBagNum, FInventoryBag& OutBag) const;
	bool GetBag(const FGuid& InBagID, FInventoryBag& OutBag) const;

	TArray<FInventoryBag> GetAllBags() const { return Bags; };

	const FInventoryBag* GetBagByType(const EBagType& InType) const;

private:

	TArray<FInventoryBag> Bags;
	int32 MaxBags;
};