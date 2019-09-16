// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/Inventory/Public/InventoryTypes/InventorySlotReference.h>

#include "TransferTargetBase.generated.h"

DEFINE_LOG_CATEGORY_STATIC(TransferTargetBaseLog, Log, Log);


UCLASS(HideDropdown)
class UTransferTargetBase : public UObject
{
	GENERATED_BODY()

public:

	virtual TOptional<InventorySlotReference> GetTarget(const InventorySlotReference& InReference ) PURE_VIRTUAL (UTransferTargetBase::GetTarget, return TOptional<InventorySlotReference>(); );
};