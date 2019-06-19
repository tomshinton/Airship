// Airship Project - Tom Shinton 2018

#include "InteractableMock.h"
#include "Components/BoxComponent.h"

AInteractableMock::AInteractableMock()
	: CollisionComp(CreateDefaultSubobject<UBoxComponent>(TEXT("TestCollision")))
{
	RootComponent = CollisionComp;

	CollisionComp->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
