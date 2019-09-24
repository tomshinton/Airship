// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/QuickTransfer/Targets/TransferTargetBase.h"

#include "TransferTargetPlayerHotbar.generated.h"

UCLASS()
class UTransferTargetPlayerHotbar : public UTransferTargetBase
{
	GENERATED_BODY()

public:

	virtual TOptional<InventorySlotReference> GetTarget(const InventorySlotReference& InReference);
};