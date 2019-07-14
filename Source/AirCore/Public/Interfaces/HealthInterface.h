// Airship Project - Tom Shinton 2018

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "Utils/Events/HealthEvents.h"

#include "HealthInterface.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, const FHealthChangeEvent&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthDepleted, const FDamagedEvent&);
DECLARE_MULTICAST_DELEGATE(FOnHealthRestored);

UINTERFACE(BlueprintType, MinimalAPI)
class UHealthInterface : public UInterface
{
	GENERATED_BODY()
};

class AIRCORE_API IHealthInterface
{
	GENERATED_BODY()

public:

	virtual void ApplyDamage(const FDamagedEvent& InDamageEvent) = 0;
	virtual void RestoreHealth(const FHealEvent& InHealEvent) = 0;

	virtual float GetCurrentHealth() const = 0;
	virtual float GetMaxHealth() const = 0;

	virtual FOnHealthDepleted& GetOnHealthDepletedEvent() = 0;
	virtual FOnHealthChanged& GetOnHealthChangedEvent() = 0;
	virtual FOnHealthRestored& GetOnHealthRestoredEvent() = 0;
};
