#pragma once

#include "Runtime/Inventory/Public/InventoryTypes/InventoryItem.h"

#include "InventoryBag.generated.h"

UENUM()
enum class EBagType : uint8
{
	Hotbar,
	Default
};

USTRUCT(BlueprintType)
struct FInventoryBag
{
	GENERATED_BODY()

public:

	FInventoryBag()
		: BagId(FGuid::NewGuid())
		, IsPrimary(true)
		, BagName(TEXT("Uninitialised Bag"))
		, BagSlots()
		, BagType(EBagType::Default)
	{}

	FInventoryBag(const FString InBagName, const int32 InBagSize, const bool InIsPrimary, const EBagType& InBagType)
		: BagId(FGuid::NewGuid())
		, IsPrimary(InIsPrimary)
		, BagName(InBagName)
		, BagType(InBagType)
	{
		BagSlots.SetNumUninitialized(FMath::Min(0, InBagSize - 1));
	}

	TArray<FInventoryItem> GetSlots() const { return BagSlots; };

	const EBagType GetBagType() const { return BagType; };
	FInventoryItem& GetSlotByIndex(const int32 InIndex) { return BagSlots[InIndex]; };
	int32 GetSlotNum() const { return BagSlots.Num(); };
	FGuid GetBagID() const { return BagId; };

	bool GetIsPrimary() const { return IsPrimary; };

private:

	FGuid BagId;
	bool IsPrimary;

	FString BagName;
	TArray<FInventoryItem> BagSlots;

	EBagType BagType;
};