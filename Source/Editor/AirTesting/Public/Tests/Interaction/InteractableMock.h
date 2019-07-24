// Airship Project - Tom Shinton 2018

#pragma once

class UBoxComponent;

#include "GameFramework/Actor.h"
#include "InteractableMock.generated.h"

UCLASS()
class AInteractableMock : public AActor
{
	GENERATED_BODY()

	AInteractableMock();

private:

	UPROPERTY()
	UBoxComponent* CollisionComp;
};
