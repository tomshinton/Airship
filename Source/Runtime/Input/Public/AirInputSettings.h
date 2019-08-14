// Airship Project - Tom Shinton 2018

#pragma once

#include "AirInputSettings.generated.h"

///////////////////////////////////////////////////////////////////////////
// GameSettings asset for Chord Lookups and Input - accessed via UnmutableDefaults or static accessor
//////////////////////////////////////////////////////////////////////////

UCLASS(config = Game, defaultconfig, MinimalAPI)
class UAirInputSettings : public UObject
{
	GENERATED_BODY()

public:

	static UAirInputSettings* Get()
	{
		return GetMutableDefault<UAirInputSettings>();
	}

	UPROPERTY(EditAnywhere, config, Category = "Input | Chord Lookup", meta = (Tooltip = "What keys count as 'chords'? For instance, Ctrl, Alt or Shift.  These are paired against other keys to facilitate discrete function calls"))
	TArray<FKey> ChordCompliments;
};
