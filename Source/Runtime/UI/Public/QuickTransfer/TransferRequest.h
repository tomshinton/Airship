// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/QuickTransfer/SlotDomain.h"

#include <Runtime/CoreUObject/Public/UObject/WeakInterfacePtr.h>
#include <Runtime/Inventory/Public/InventoryInterface.h>

struct FTransferTarget
{
	FTransferTarget(const TWeakInterfacePtr<IInventoryInterface>& InTargetInterface, const uint32 InTargetIndex)
		: TargetInterface(InTargetInterface)
		, TargetIndex(InTargetIndex)
	{}

	UPROPERTY()
	TWeakInterfacePtr<IInventoryInterface> TargetInterface;

	uint32 TargetIndex;
};

class FTransferRequest
{
	FTransferRequest(const TWeakInterfacePtr<IInventoryInterface>& InSourceInterface, const uint32 InSourceIndex)
		: SourceInterface(*SourceInterface)
		, SourceIndex(InSourceIndex)
	{}

private:

	UPROPERTY()
	TWeakInterfacePtr<IInventoryInterface> SourceInterface;

	uint32 SourceIndex;
	
	virtual bool Transfer() = 0;
	virtual const FTransferTarget& GetTransferTarget(IInventoryInterface& RequestingInventory) const = 0;
};