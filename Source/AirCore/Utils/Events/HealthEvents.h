// Airship Project - Tom Shinton 2018

#pragma once

#include "UnrealMathUtility.h"
#include "HealthEvents.generated.h"

UENUM()
enum class EDamageType : uint8 
{
	None, //Invalid DamageType - should force a bail if this is passed to the HealthComponent
	Flat, //Mapped against nothing - applies the value outright
	Falling, //Mapped to owners velocity
};

UENUM()
enum class EHealType : uint8
{
	None, //Invalid HealType - should force a bail if this is passed to the HealthComponent
	Flat, //Mapped against nothing, applies the value outright
	Regen //Also flat
};


USTRUCT()
struct FDamagedEvent
{
	GENERATED_BODY()

	FDamagedEvent()
		: DamageEventID(FGuid::NewGuid())
		, Amount(0.f)
		, DamageType(EDamageType::None)
		, Instigator(nullptr)
	{}

	FDamagedEvent(const float& InAmount, const EDamageType& InDamageType, UObject* InInstigator)
		: DamageEventID(FGuid::NewGuid())
		, Amount(InAmount)
		, DamageType(InDamageType)
		, Instigator(InInstigator)
	{}

public:

	bool operator==(const FDamagedEvent& OtherEvent) const
	{
		return OtherEvent.DamageEventID == DamageEventID;
	}

	FGuid DamageEventID;

	float Amount;

	EDamageType DamageType;

	UPROPERTY()
	UObject* Instigator;
};

USTRUCT()
struct FHealEvent
{
	GENERATED_BODY()

	FHealEvent()
		: HealEventID(FGuid::NewGuid())
		, Amount(0.f)
		, HealType(EHealType::None)
		, Instigator(nullptr)
	{}

	FHealEvent(const float& InAmount, const EHealType& InDamageType, UObject* InInstigator)
		: HealEventID(FGuid::NewGuid())
		, Amount(InAmount)
		, HealType(InDamageType)
		, Instigator(InInstigator)
	{}

public:

	bool operator==(const FHealEvent& OtherEvent) const
	{
		return OtherEvent.HealEventID == HealEventID;
	}

	FGuid HealEventID;

	float Amount;

	EHealType HealType;

	UPROPERTY()
	UObject* Instigator;
};

USTRUCT()
struct FHealthChangeEvent
{
	GENERATED_BODY()

	FHealthChangeEvent()
		: HealthEventID(FGuid())
		, Amount(0.f)
		, HasIncreased(false)
	{}

	FHealthChangeEvent(const FDamagedEvent& InDamagedEvent)
		: HealthEventID(InDamagedEvent.DamageEventID)
		, Amount(InDamagedEvent.Amount)
		, HasIncreased(false)
	{}

	FHealthChangeEvent(const FHealEvent& InHealEvent)
		: HealthEventID(InHealEvent.HealEventID)
		, Amount(InHealEvent.Amount)
		, HasIncreased(true)
	{}

	bool operator==(const FDamagedEvent& OtherEvent) const
	{
		return OtherEvent.DamageEventID == HealthEventID;
	}

	bool operator==(const FHealEvent& OtherEvent) const
	{
		return OtherEvent.HealEventID == HealthEventID;
	}

	bool operator==(const FHealthChangeEvent& OtherEvent) const
	{
		return OtherEvent.HealthEventID == HealthEventID;
	}

public:

	FGuid HealthEventID;

	float Amount;
	bool HasIncreased;
};