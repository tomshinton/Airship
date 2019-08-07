// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/CoreUObject/Public/UObject/Interface.h>

#include "OverlayLockInterface.generated.h"

UINTERFACE(MinimalAPI)
class UOverlayLockInterface : public UInterface
{
	GENERATED_BODY()
};

class UI_API IOverlayLockInterface
{
	GENERATED_BODY()

public:

	virtual bool ShouldLockOverlay() const = 0;
};
