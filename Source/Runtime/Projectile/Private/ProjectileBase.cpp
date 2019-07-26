// Airship Project - Tom Shinton 2018

#include "Runtime/Projectile/Public/ProjectileBase.h"

AProjectileBase::AProjectileBase()
	: ProjectileVelocity(0.f)
	, MoveDirection(FVector::ZeroVector)
{}

void AProjectileBase::OnFire(const FVector& InFireDirection)
{

}
