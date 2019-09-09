// Airship Project - Tom Shinton 2018

#pragma once

#include <GameFramework/PlayerController.h>
#include <GameFramework/PlayerInput.h>
#include "Kismet/BlueprintFunctionLibrary.h"

#include "BindingFunctions.generated.h"

UCLASS(MinimalAPI)
class UBindingFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = Binding)
	static void GetKeysForAction(const FName& Action, const APlayerController* Controller, TArray<FInputActionKeyMapping>& OutBindings)
	{
		if (Controller)
		{
			OutBindings = Controller->PlayerInput->GetKeysForAction(Action);
		}
	}
};

