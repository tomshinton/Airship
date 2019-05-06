// Airship Project - Tom Shinton 2018

#pragma once

class UAirHUDBase;

#include "UISettings.generated.h"

///////////////////////////////////////////////////////////////////////////
// GameSettings asset for global assets - accessed via UnmutableDefaults
//////////////////////////////////////////////////////////////////////////

UCLASS(config = Game, defaultconfig, MinimalAPI)
class UUISettings : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, config, Category = "UI")
	TSubclassOf<UAirHUDBase> HUDWidget;
};
