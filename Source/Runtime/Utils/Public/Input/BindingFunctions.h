// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/Engine/Classes/GameFramework/PlayerController.h>
#include <Runtime/Engine/Classes/GameFramework/PlayerInput.h>
#include <Runtime/Engine/Classes/Kismet/BlueprintFunctionLibrary.h>

#include "BindingFunctions.generated.h"

UCLASS()
class UTILS_API UBindingFunctions : public UBlueprintFunctionLibrary
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

