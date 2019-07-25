// Airship Project - Tom Shinton 2018

#pragma once

#include "InventoryViewInterface.generated.h"

class UAirInventory;

UINTERFACE()
class UInventoryViewInterface : public UInterface
{
	GENERATED_BODY()
};

class INVENTORY_API IInventoryViewInterface
{
	GENERATED_BODY()

public:

	virtual void SetLinkedInventory(UAirInventory* InAirInventory) = 0;
};
