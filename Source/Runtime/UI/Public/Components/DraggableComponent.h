// Airship Project - Tom Shinton 2018

#pragma once

#include <Engine/Classes/Components/ActorComponent.h>

#include "DraggableComponent.generated.h"

UCLASS(Within = UserWidget, NotBlueprintable, NotBlueprintType)
class UDraggableComponent : public UActorComponent
{
	GENERATED_BODY()

	UDraggableComponent();
};
