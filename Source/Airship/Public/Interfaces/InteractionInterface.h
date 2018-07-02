#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

#include "InteractionInterface.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class AIRSHIP_API IInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interaction)
	void OnInteract();
};
