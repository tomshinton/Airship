// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/QuickTransfer/SlotFinder/SlotFinder.h"

class InventoryBagReference;

DEFINE_LOG_CATEGORY_STATIC(InvBagFinderLog, Log, Log);

class UI_API BagFinder
{

public:
	
	BagFinder()
		: InvSlotFinder()
	{};

	BagFinder(UWorld& InWorldContext, const TOptional<ESlotDomain>& InSlotDomainFilter, const TArray<ESlateVisibility>& InSlateVisibilityFilters) 
		: InvSlotFinder(InWorldContext, InSlotDomainFilter, InSlateVisibilityFilters)
	{};

	TArray<InventoryBagReference> Get() const;

private:

	SlotFinder InvSlotFinder;
};