// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/QuickTransfer/Targets/TransferTargetBase.h"

#include "TransferTargetPlayerBackpack.generated.h"

UCLASS()
class UTransferTargetPlayerBackpack : public UTransferTargetBase
{
	GENERATED_BODY()

public:

	virtual TOptional<InventorySlotReference> GetTarget(const InventorySlotReference& InReference);
};