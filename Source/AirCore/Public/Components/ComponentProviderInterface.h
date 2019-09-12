// Airship Project - Tom Shinton 2018

#pragma once

#include "Interface.h"

class UHealthComponent;
class UAirInventory;

#include "ComponentProviderInterface.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UComponentProviderInterface : public UInterface
{
	GENERATED_BODY()
};

class AIRCORE_API IComponentProviderInterface
{
	GENERATED_BODY()

public:

	virtual UHealthComponent* GetHealthComponent() const = 0;
	virtual UAirInventory* GetInventoryComponent() const = 0;
};
