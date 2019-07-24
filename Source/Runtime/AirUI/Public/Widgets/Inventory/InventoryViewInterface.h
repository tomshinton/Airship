// Airship Project - Tom Shinton 2018

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

#include "InventoryViewInterface.generated.h"

class UAirInventory;

UINTERFACE()
class UInventoryViewInterface : public UInterface
{
	GENERATED_BODY()
};

class AIRUI_API IInventoryViewInterface
{
	GENERATED_BODY()

public:

	virtual void SetLinkedInventory(UAirInventory* InAirInventory) = 0;
};
