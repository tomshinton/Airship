// Airship Project - Tom Shinton 2018

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Engine/DataTable.h>
#include "AirSettings.generated.h"

///////////////////////////////////////////////////////////////////////////
// GameSettings asset for global assets - accessed via UnmutableDefaults
//////////////////////////////////////////////////////////////////////////

UCLASS(config = Game, defaultconfig)
class AIRSHIP_API UAirSettings : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, config, Category = "Inventory", meta = (AllowedClasses = "DataTable"))
	FStringAssetReference InventoryLookup;
};
