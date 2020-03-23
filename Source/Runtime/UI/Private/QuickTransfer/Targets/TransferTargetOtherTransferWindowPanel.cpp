// Airship Project - Tom Shinton 2018

#include "Runtime/UI/Public/QuickTransfer/Targets/TransferTargetOtherTransferWindowPanel.h"

#include <Runtime/Inventory/Public/InventoryFunctions.h>
#include <Runtime/Inventory/Public/InventoryTypes/InventoryBagReference.h>

UTransferTargetOtherTransferWindowBase::UTransferTargetOtherTransferWindowBase()
	: InvBagFinder(*GetWorld(), ESlotDomain::TransferWindow, {ESlateVisibility::Visible, ESlateVisibility::SelfHitTestInvisible, ESlateVisibility::HitTestInvisible})
{}

TOptional<InventorySlotReference> UTransferTargetOtherTransferWindowBase::GetTarget(const InventorySlotReference& InReference)
{
	TArray<InventoryBagReference> RepresentedBags = InvBagFinder.Get();
	
	const int32 IndexOfOwningInventory = RepresentedBags.IndexOfByPredicate([&InReference](const InventoryBagReference& FoundBagRef)
	{
		return FoundBagRef.BagReference == InReference.BagReference;
	});

	if (IndexOfOwningInventory != INDEX_NONE)
	{
		RepresentedBags.RemoveAtSwap(IndexOfOwningInventory);
	}

	if (RepresentedBags.Num() > 0 && RepresentedBags.IsValidIndex(0))
	{
		return InventoryFunctions::GetFirstEmptySlotInBag(*RepresentedBags[0].AssociatedInventory, RepresentedBags[0].BagReference);
	}

	return TOptional<InventorySlotReference>();
}
