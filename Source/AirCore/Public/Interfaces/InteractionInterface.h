#pragma once

#include "CoreMinimal.h"
#include "Interface.h"

#include "InteractionInterface.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class AIRCORE_API IInteractionInterface
{
	GENERATED_BODY()

public:

	virtual void OnInteract(AActor* InteractingActor) = 0;
};
