// ColonyBuilder Project, personal project by Tom Shinton

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "Utils/Events/DamageEvents.h"

#include "HealthInterface.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, const FBaseDamageEvent&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthDepleted, const FBaseDamageEvent&);

UINTERFACE(BlueprintType, MinimalAPI)
class UHealthInterface : public UInterface
{
	GENERATED_BODY()
};

class AIRCORE_API IHealthInterface
{
	GENERATED_BODY()

public:
	virtual void ApplyDamage(const FBaseDamageEvent& InDamageEvent) = 0;

	virtual FOnHealthDepleted& GetOnHealthDepletedEvent() = 0;
	virtual FOnHealthChanged& GetOnHealthChangedEvent() = 0;
};
