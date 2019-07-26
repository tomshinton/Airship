// Airship Project - Tom Shinton 2018

#pragma once

#include "ProjectileBase.generated.h"

//////////////////////////////////////////////////////////////////////////
// Base projectile for all projectiles
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI)
class AProjectileBase : public AActor
{
	GENERATED_BODY()

public:

	AProjectileBase();

	virtual void OnFire(const FVector& InFireDirection);

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float ProjectileVelocity;

private:

	FVector MoveDirection;
};
