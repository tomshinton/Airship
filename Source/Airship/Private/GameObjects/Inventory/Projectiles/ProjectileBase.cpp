// Airship Project - Tom Shinton 2018

#include "ProjectileBase.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);
}

void AProjectileBase::OnFire(const FVector FireDirection)
{
	MoveDirection = FireDirection;
	ItemMesh->AddImpulse(MoveDirection*ProjectileVelocity);
}