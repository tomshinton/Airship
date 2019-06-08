#pragma once

#include "Clip.h"
#include "Engine/DataTable.h"

#include "InventoryItemRow.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct AIRCORE_API FInventoryItemRow : public FTableRowBase
{
public:

	GENERATED_BODY()

	FInventoryItemRow()
	: IsNullSlot(true)
	, ItemIcon(nullptr)
	{}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemInfo)
	bool IsNullSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemInfo)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemInfo)
	FString ItemNameReadable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemInfo)
	FString ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
	UTexture2D* ItemIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
	TSubclassOf<class AWorldItem> ItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
	bool Stacks;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
	int32 StackSize;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
	FClip Clip;
};