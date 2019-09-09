// Airship Project - Tom Shinton 2018

#pragma once

#include "CoreMinimal.h"
#include "Interface.h"
#include "InteractableInterface.h"

#include "InteractionInterface.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewItemHovered, IInteractableInterface*);

UINTERFACE(BlueprintType, MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class AIRCORE_API IInteractionInterface
{
	GENERATED_BODY()

public:

	virtual FOnNewItemHovered& GetOnNewItemHoveredDelegate() = 0;
};
