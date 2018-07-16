#pragma once

#include "DamageEvents.generated.h"

UENUM()
enum class EDamageType : uint8 
{
	None,
	Falling,
	Projectile,
	Explosion
};

USTRUCT()
struct FBaseDamageEvent
{
	GENERATED_BODY()

		FBaseDamageEvent()
		: Amount(0.f)
		, DamageType(EDamageType::None)
		, Instigator(nullptr)
	{}

	FBaseDamageEvent(const float InAmount, EDamageType InDamageType, UObject* InInstigator)
		: Amount(InAmount)
		, DamageType(InDamageType)
		, Instigator(InInstigator)
	{}

public:
	float Amount;
	EDamageType DamageType;
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