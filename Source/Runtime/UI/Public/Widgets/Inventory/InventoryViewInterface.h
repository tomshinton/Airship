// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/CoreUObject/Public/UObject/Interface.h>

#include "Runtime/UI/Public/QuickTransfer/SlotDomain.h"

#include "InventoryViewInterface.generated.h"

class IInventoryInterface;

UINTERFACE(MinimalAPI)
class UInventoryViewInterface : public UInterface
{
	GENERATED_BODY()
};

class UI_API IInventoryViewInterface
{
	GENERATED_BODY()

public:

	virtual void SetLinkedInventory(IInventoryInterface* InInterface, const FGuid& InBagID) = 0;
	virtual void SetSlotDomain(const ESlotDomain InDomain) = 0;
};
