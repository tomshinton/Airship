// Airship Project - Tom Shinton 2018

#pragma once

#include "GameFramework/CheatManager.h"
#include "AirCheatManager.generated.h"

class AAirChar;
class AAirController;

UCLASS()
class AIRCORE_API UAirCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	UAirCheatManager();

	AAirChar* GetAirCharacter() const;
	AAirController* GetAirController() const;

	UFUNCTION(Exec, Category = "Health")
	void AddPlayerHealth(const float HealthToAdd);
};
