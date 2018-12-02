// Airship Project - Tom Shinton 2018

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AirGameInst.generated.h"

//////////////////////////////////////////////////////////////////////////
// base GameInstance for AirProject
//////////////////////////////////////////////////////////////////////////

UCLASS()
class AIRSHIP_API UAirGameInst : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

};
