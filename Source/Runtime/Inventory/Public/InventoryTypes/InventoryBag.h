// Airship Project - Tom Shinton 2018

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
		: IsPrimary(true)
		, BagName(TEXT("Uninitialised Bag"))
		, BagId(FGuid::NewGuid())
		, BagSlots()
		, BagType(EBagType::Default)
	{}

	FInventoryBag(const bool InIsPrimary, const FString& InBagName, const EBagType& InBagType, const int32 InBagSize)
		: IsPrimary(InIsPrimary)
		, BagName(InBagName)
		, BagId(FGuid::NewGuid())
		, BagType(InBagType)
	{
		BagSlots.Empty();

		for (int32 i = 0; i < InBagSize; ++i)
		{
			BagSlots.Add(FInventoryItem());
		}
	}

	TArray<FInventoryItem> GetSlots() const { return BagSlots; };

	const EBagType GetBagType() const { return BagType; };
	FInventoryItem& GetSlotByIndex(const int32 InIndex) { return BagSlots[InIndex]; };
	int32 GetSlotNum() const { return BagSlots.Num(); };
	FGuid GetBagID() const { return BagId; };

	bool GetIsPrimary() const { return IsPrimary; };

	UPROPERTY(EditDefaultsOnly)
	bool IsPrimary;

	UPROPERTY(EditDefaultsOnly)
	FString BagName;

private:

	FGuid BagId;
	   
	TArray<FInventoryItem> BagSlots;

	EBagType BagType;
};