// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/QuickTransfer/Targets/TransferTargetBase.h"

#include "Runtime/UI/Public/QuickTransfer/BagFinder/BagFinder.h"

#include "TransferTargetOtherTransferWindowPanel.generated.h"

UCLASS()
class UTransferTargetOtherTransferWindowBase : public UTransferTargetBase
{
	GENERATED_BODY()

public:

	UTransferTargetOtherTransferWindowBase();

	virtual TOptional<InventorySlotReference> GetTarget(const InventorySlotReference& InReference);

private:

	BagFinder InvBagFinder;
};