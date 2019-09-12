// Airship Project - Tom Shinton 2018

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventorySlotPayload.generated.h"

class UInventorySlot;

UCLASS()
class UInventorySlotPayload : public UObject
{
	GENERATED_BODY()

public:

	UInventorySlot* SourceInventorySlot;	
};
