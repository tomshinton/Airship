// Airship Project - Tom Shinton 2018

#pragma once

#include "AirSettings.generated.h"

///////////////////////////////////////////////////////////////////////////
// GameSettings asset for global assets - accessed via UnmutableDefaults
//////////////////////////////////////////////////////////////////////////

UCLASS(config = Game, defaultconfig, MinimalAPI)
class UAirSettings : public UObject
{
	GENERATED_BODY()

public:

	static UAirSettings* Get()
	{
		return GetMutableDefault<UAirSettings>();
	}
};
