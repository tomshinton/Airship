// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/QuickTransfer/SlotDomain.h"

class InventorySlotReference;

DECLARE_LOG_CATEGORY_EXTERN(TransferRequestLog, All, All);

class TransferRequest
{
public:

	static void RequestTransfer(const InventorySlotReference& InRequestingSlot, const ESlotDomain InDomain, UObject& InTransferTargetLookup);
};