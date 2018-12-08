// Airship Project - Tom Shinton 2018

#pragma once

#include "CoreMinimal.h"
#include "GameObjects/Inventory/WorldItem.h"
#include "ProjectileBase.generated.h"

//////////////////////////////////////////////////////////////////////////
// Base projectile for all projectiles
//////////////////////////////////////////////////////////////////////////

UCLASS()
class AIRSHIP_API AProjectileBase : public AWorldItem
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
