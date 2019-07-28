// Airship Project - Tom Shinton 2018

#pragma once

#include "Interface.h"
#include "HotbarInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHotbarInterface : public UInterface
{
	GENERATED_BODY()
};

class INVENTORY_API IHotbarInterface
{
	GENERATED_BODY()

public:

	virtual int32 GetNumHotbarSlots() const = 0;
};
