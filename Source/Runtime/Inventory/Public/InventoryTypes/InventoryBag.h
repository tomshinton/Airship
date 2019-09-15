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
		, SlotsNum(0)
		, BagType(EBagType::Default)
		, BagId(FGuid::NewGuid())
		, BagSlots()
	{}

	FInventoryBag(const bool InIsPrimary, const FString& InBagName, const EBagType& InBagType, const int32 InBagSize)
		: IsPrimary(InIsPrimary)
		, BagName(InBagName)
		, SlotsNum(InBagSize)
		, BagType(InBagType)
		, BagId(FGuid::NewGuid())
	{}

	void InitSlots()
	{
		BagSlots.Empty();

		for (int32 i = 0; i < SlotsNum; ++i)
		{
			BagSlots.Add(FInventoryItem(BagId));
		}
	}

	const EBagType GetBagType() const { return BagType; };
	FInventoryItem& GetSlotByIndex(const int32 InIndex) { return BagSlots[InIndex]; };
	int32 GetSlotNum() const { return BagSlots.Num(); };
	FGuid GetBagID() const { return BagId; };

	bool GetIsPrimary() const { return IsPrimary; };

	UPROPERTY(EditDefaultsOnly)
	bool IsPrimary;

	UPROPERTY(EditDefaultsOnly)
	FString BagName;

	UPROPERTY(EditDefaultsOnly)
	int32 SlotsNum;

	UPROPERTY(EditDefaultsOnly)
	EBagType BagType;

	UPROPERTY(VisibleAnywhere)
	FGuid BagId;

	TArray<FInventoryItem> BagSlots;
};