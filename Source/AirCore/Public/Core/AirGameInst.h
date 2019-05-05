// Airship Project - Tom Shinton 2018

#pragma once

#include "Engine/GameInstance.h"
#include "AirGameInst.generated.h"

//////////////////////////////////////////////////////////////////////////
// base GameInstance for AirProject
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI)
class UAirGameInst : public UGameInstance
{
	GENERATED_BODY()

public:
	AIRCORE_API virtual void Init() override;
};
