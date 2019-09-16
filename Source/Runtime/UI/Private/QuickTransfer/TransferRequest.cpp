// Airship Project - Tom Shinton 2018

#include "Runtime/UI/Public/QuickTransfer/TransferRequest.h"

#include "Runtime/UI/Public/QuickTransfer/Targets/TransferTargetBase.h"
#include "Runtime/UI/Public/QuickTransfer/TransferRequestTargetDataAsset.h"

#if !UE_BUILD_SHIPPING
#include <Runtime/Utils/Public/Enum/EnumHelpers.h>
#endif //!UE_BUILD_SHIPPING

#include <Runtime/Inventory/Public/InventoryTypes/InventorySlotReference.h>

DEFINE_LOG_CATEGORY(TransferRequestLog);

void TransferRequest::RequestTransfer(const InventorySlotReference& InRequestingSlot, const ESlotDomain InDomain, UObject& InTransferTargetLookup)
{
#if !UE_BUILD_SHIPPING
	UE_LOG(TransferRequestLog, Log, TEXT("Quick Transfer request issued from %s - slot %i, with domain %s"), *InRequestingSlot.BagReference.ToString(), InRequestingSlot.SlotNumberReference, *EnumHelpers::EnumToString<ESlotDomain>("ESlotDomain", InDomain));
#endif //!UE_BUILD_SHIPPING

	if (UTransferRequestTargetDataAsset* TransferLookup = CastChecked<UTransferRequestTargetDataAsset>(&InTransferTargetLookup))
	{
		if (const FTransferTarget* Targets = TransferLookup->Targets.Find(InDomain))
		{
#if !UE_BUILD_SHIPPING
			UE_LOG(TransferRequestLog, Log, TEXT("Found a transfer target for domain %s - spinning up lookup targets"), *EnumHelpers::EnumToString<ESlotDomain>("ESlotDomain", InDomain));
#endif //!UE_BUILD_SHIPPING

			for (const TSubclassOf<UTransferTargetBase>& Target : Targets->TransferTargets)
			{
				if (UTransferTargetBase* NewTarget = NewObject<UTransferTargetBase>(GetTransientPackage(), Target))
				{
					TOptional<InventorySlotReference> RespondingTarget = NewTarget->GetTarget(InRequestingSlot);

					if (RespondingTarget.IsSet())
					{
#if !UE_BUILD_SHIPPING
						UE_LOG(TransferRequestLog, Log, TEXT("Found a transfer response for domain %s - returning"), *EnumHelpers::EnumToString<ESlotDomain>("ESlotDomain", InDomain));
#endif //!UE_BUILD_SHIPPING

						return;
					}
				}
			}
		}
	}
}
