// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/Widgets/Inventory/InventorySlot.h"
#include "Runtime/UI/Public/QuickTransfer/SlotDomain.h"

#include <Runtime/CoreUObject/Public/UObject/UObjectIterator.h>
#include <Runtime/Engine/Classes/Engine/World.h>
#include <Runtime/Inventory/Public/InventoryTypes/InventoryBag.h>
#include <Runtime/Inventory/Public/InventoryTypes/InventorySlotReference.h>

DEFINE_LOG_CATEGORY_STATIC(InvSlotFinderLog, Log, Log);

class SlotFinder
{

public:

	SlotFinder()
		: WorldContext(nullptr)
		, SlotDomainFilter()
		, SlateVisibilityFilters()
	{};

	SlotFinder(UWorld& InWorldContext, const TOptional<ESlotDomain>& InSlotDomainFilter, const TArray<ESlateVisibility>& InSlateVisibilityFilters)
		: WorldContext(&InWorldContext)
		, SlotDomainFilter(InSlotDomainFilter)
	{
		const TArray<ESlateVisibility> InSlateVisibilityFiltersFromList = InSlateVisibilityFilters;
		if (InSlateVisibilityFilters.Num() > 0)
		{
			SlateVisibilityFilters = InSlateVisibilityFiltersFromList;
		}
	};

	TArray<InventorySlotReference> Get() const
	{
		TArray<InventorySlotReference> FoundSlots;
		for (TObjectIterator<UInventorySlot> Itr; Itr; ++Itr)
		{
			if (UInventorySlot* InventorySlot = *Itr)
			{
				if (SlotMatchesFilters(*InventorySlot))
				{
#if !UE_BUILD_SHIPPING
					UE_LOG(InvSlotFinderLog, Log, TEXT("Found Slot matching filters - %s"), *InventorySlot->GetName());
#endif //!UE_BUILD_SHIPPING

					FoundSlots.Add(InventorySlot->GetSlotRef());
				}
			}
		}

#if !UE_BUILD_SHIPPING
		UE_LOG(InvSlotFinderLog, Log, TEXT("Found %i valid slots"), FoundSlots.Num());
#endif //!UE_BUILD_SHIPPING

		return FoundSlots;
	};

	bool SlotMatchesFilters(const UInventorySlot& InSlot) const;

	static bool SlotMatchesDomainFilter(const UInventorySlot& InSlot, const TOptional<ESlotDomain>& InSlotDomainFilter);;
	static bool SlotMatchesSlateVisibilityFilter(const UInventorySlot& InSlot, const TOptional<TArray<ESlateVisibility>>& InSlateVisibilityFilters);
	static bool SlotIsValidPointer(const UInventorySlot& InSlot);

private:

	UPROPERTY()
	UWorld* WorldContext;

	TOptional<ESlotDomain> SlotDomainFilter;
	TOptional<TArray<ESlateVisibility>> SlateVisibilityFilters;
};