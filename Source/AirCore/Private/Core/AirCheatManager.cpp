// Airship Project - Tom Shinton 2018

#include "AirCheatManager.h"
#include "AirController.h"
#include "Engine/World.h"
#include "AirChar.h"
#include "HealthComponent.h"
#include "Utils/Events/HealthEvents.h"

UAirCheatManager::UAirCheatManager()
{

}

AAirChar* UAirCheatManager::GetAirCharacter() const
{
	if (AAirController* AirController = GetAirController())
	{
		return Cast<AAirChar>(AirController->GetPawn());
	}

	return nullptr;
}

AAirController* UAirCheatManager::GetAirController() const
{
	if (UWorld* World = GetWorld())
	{
		return Cast<AAirController>(World->GetFirstPlayerController());
	}

	return nullptr;
}

void UAirCheatManager::AddPlayerHealth(const float HealthToAdd)
{
	if (AAirChar* Char = GetAirCharacter())
	{
		if (IComponentProviderInterface* CompProvider = Cast<IComponentProviderInterface>(Char))
		{
			if (UHealthComponent* HealthComp = CompProvider->GetHealthComponent())
			{
				if (IHealthInterface* HealthInterface = Cast<IHealthInterface>(HealthComp))
				{
					HealthInterface->RestoreHealth(FHealEvent(100.f, EHealType::Flat, Char));
				}
			}		
		}
	}
}
