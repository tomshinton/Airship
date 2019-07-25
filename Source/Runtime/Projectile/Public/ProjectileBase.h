// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/Item/Public/WorldItem.h>

#include "ProjectileBase.generated.h"

//////////////////////////////////////////////////////////////////////////
// Base projectile for all projectiles
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI)
class AProjectileBase : public AWorldItem
{
	GENERATED_BODY()

	AProjectileBase();

public:
	virtual void OnFire(const FVector FireDirection);

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FVector MoveDirection;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float ProjectileVelocity;
};
