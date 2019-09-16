// Airship Project - Tom Shinton 2018

#pragma once

#include "SlotDomain.generated.h"

UENUM(BlueprintType)
enum class ESlotDomain : uint8
{
	Default,
	Hotbar,
	Bag,
	TransferWindow
};