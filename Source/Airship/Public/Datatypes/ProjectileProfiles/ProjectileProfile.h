// Airship Project - Tom Shinton 2018

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectileProfile.generated.h"


UCLASS(Blueprintable, BlueprintType)
class AIRSHIP_API UProjectileProfile : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Test")
	float Test;
};
