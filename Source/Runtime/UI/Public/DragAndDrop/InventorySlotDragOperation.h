// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/Inventory/Public/InventoryTypes/InventorySlotReference.h>
#include <Runtime/UMG/Public/Blueprint/DragDropOperation.h>

#include "InventorySlotDragOperation.generated.h"

UCLASS()
class UInventorySlotDragOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:

	InventorySlotReference OutgoingSlot;
};
