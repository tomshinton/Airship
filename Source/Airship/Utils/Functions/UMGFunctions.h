#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>
#include "AirWidget.h"
#include "UMGFunctions.generated.h"

UCLASS()
class AIRSHIP_API UUMGFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "AirUMG | Spawning")
	static UAirWidget* CreateAirWidget(UWorld* World, TSubclassOf<UAirWidget> Class)
	{
		if (UAirWidget* SpawnedWidget = Cast<UAirWidget>(CreateWidget<UAirWidget>(World, Class)))
		{
			SpawnedWidget->Build();
		
			return SpawnedWidget;
		}

		return nullptr;
	}

};

