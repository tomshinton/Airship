// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/CoreUObject/Public/UObject/Interface.h>

#include "InventoryViewInterface.generated.h"

class IHotbarInterface;
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

	virtual void SetLinkedInventory(IInventoryInterface* InInterface) = 0;
	virtual void SetLinkedHotbar(IHotbarInterface* InInterface) = 0;
};
