// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/QuickTransfer/SlotFinder/SlotFinder.h"

bool SlotFinder::SlotMatchesFilters(const UInventorySlot& InSlot)
{
	return
		SlotMatchesDomainFilter(InSlot, SlotDomainFilter) &&
		SlotMatchesSlateVisibilityFilter(InSlot, SlateVisibilityFilters) &&
		SlotIsValidPointer(InSlot);
}

bool SlotFinder::SlotMatchesDomainFilter(const UInventorySlot& InSlot, const TOptional<ESlotDomain>& InSlotDomainFilter)
{
	if (!InSlotDomainFilter.IsSet())
	{
		return true;
	}

	const bool Match = InSlot.GetSlotDomain() == InSlotDomainFilter.GetValue();
	return Match;
}

bool SlotFinder::SlotMatchesSlateVisibilityFilter(const UInventorySlot& InSlot, const TOptional<TArray<ESlateVisibility>>& InSlateVisibilityFilters)
{
	if (!InSlateVisibilityFilters.IsSet())
	{
		return true;
	}
	
	for (const ESlateVisibility& Filter : InSlateVisibilityFilters.GetValue())
	{
		if (InSlot.GetVisibility() == Filter)
		{
				return true;
		}
	}

	return false;
}

bool SlotFinder::SlotIsValidPointer(const UInventorySlot& InSlot)
{
	const bool Match = InSlot.IsValidLowLevel() && InSlot.IsConstructed();
	return Match;
}
