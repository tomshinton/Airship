// Airship Project - Tom Shinton 2018

#pragma once

#include "InventoryViewInterface.generated.h"

class UAirInventory;

UINTERFACE(MinimalAPI)
class UInventoryViewInterface : public UInterface
{
	GENERATED_BODY()
};

class UI_API IInventoryViewInterface
{
	GENERATED_BODY()

public:

	virtual void SetLinkedInventory(UAirInventory* InAirInventory) = 0;
};
