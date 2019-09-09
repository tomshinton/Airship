// Airship Project - Tom Shinton 2018

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

#include "InteractableInterface.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class AIRCORE_API IInteractableInterface
{
	GENERATED_BODY()

public:

	virtual void OnInteract(AActor* InteractingActor) = 0;
	virtual FText GetDisplayName() const = 0;
};
