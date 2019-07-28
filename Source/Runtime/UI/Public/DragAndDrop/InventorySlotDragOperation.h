// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/Widgets/Inventory/InventorySlot.h"

#include <Runtime/UMG/Public/Blueprint/DragDropOperation.h>
#include <Runtime/Inventory/Public/InventoryInterface.h>

#include "InventorySlotDragOperation.generated.h"

UCLASS()
class UInventorySlotDragOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "IncomingSlot", ExposeOnSpawn = true), Category = "Slot Info")
	UInventorySlot* IncomingSlot;

	TScriptInterface<IInventoryInterface> SourceInventoryInterface;
};
