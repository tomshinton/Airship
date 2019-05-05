#pragma once

#include <GameFramework/PlayerController.h>
#include <GameFramework/PlayerInput.h>

#include "BindingFunctions.generated.h"

UCLASS()
class UBindingFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = Binding)
	static void GetKeysForAction(FName Action, APlayerController* Controller, TArray<FInputActionKeyMapping>& Bindings)
	{
		if (Controller)
		{
			Bindings = Controller->PlayerInput->GetKeysForAction(Action);
		}
	}
};

