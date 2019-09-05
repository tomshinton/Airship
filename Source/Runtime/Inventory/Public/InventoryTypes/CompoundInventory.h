// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/Inventory/Public/InventoryTypes/InventoryBag.h"

class CompoundInventory
{

public:

	CompoundInventory();
	~CompoundInventory();

	CompoundInventory(const TArray<FInventoryBag>& InDefaultBags, const int32 InMaxBags);
	   
	void AddBag(const FInventoryBag& InNewBag);

	bool GetBag(const int32 InBagNum, FInventoryBag& OutBag) const;
	FInventoryBag* GetBag(const FGuid& InBagID) const;

	TArray<FInventoryBag> GetAllBags() const { return Bags; };

	const FInventoryBag* GetBagByType(const EBagType& InType) const;
	void GetSlotByID(const FGuid& InBagID, const FGuid& InSlotID, FInventoryItem& OutSlot);

private:

	TArray<FInventoryBag> Bags;
	int32 MaxBags;
};