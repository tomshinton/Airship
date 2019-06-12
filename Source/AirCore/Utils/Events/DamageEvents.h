#pragma once

#include "UnrealMathUtility.h"
#include "DamageEvents.generated.h"

UENUM()
enum class EDamageType : uint8 
{
	None, //Invalid DamageType - should force a bail if this is passed to the HealthComponent
	Flat, //Mapped against nothing - applies the value outright
	Falling, //Mapped to owners velocity
};

USTRUCT()
struct FBaseDamageEvent
{
	GENERATED_BODY()

		FBaseDamageEvent()
		: DamageEventID(FGuid::NewGuid())
		, Amount(0.f)
		, DamageType(EDamageType::None)
		, Instigator(nullptr)
	{}

	FBaseDamageEvent(const float& InAmount, const EDamageType& InDamageType, UObject* InInstigator)
		: DamageEventID(FGuid::NewGuid())
		, Amount(InAmount)
		, DamageType(InDamageType)
		, Instigator(InInstigator)
	{}

public:

	bool operator==(const FBaseDamageEvent& OtherEvent) const
	{
		return OtherEvent.DamageEventID == DamageEventID;
	}

	FGuid DamageEventID;

	float Amount;

	EDamageType DamageType;

	UPROPERTY()
	UObject* Instigator;

	void Overview()
	{
		if (Instigator)
		{
			FString DamageCallback = "DamageEvent: " + FString::SanitizeFloat(Amount) + " inflicted by " + (Instigator ? Instigator->GetName() : " None");
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::White, DamageCallback);
		}
	}
};