// ColonyBuilder Project, personal project by Tom Shinton

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "Events/DamageEvents.h"

#include "HealthInterface.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UHealthInterface : public UInterface
{
	GENERATED_BODY()
};

class AIRSHIP_API IHealthInterface
{
	GENERATED_BODY()

public:
	virtual void ApplyDamage(const FBaseDamageEvent& InDamageEvent) =0;
};
