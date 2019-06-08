#pragma once

#include "Clip.generated.h"

class AProjectileBase;

USTRUCT(Blueprintable, BlueprintType)
struct AIRCORE_API FClip
{
	GENERATED_BODY()

	FClip()
	: CurrentClip(0)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
	FName AmmoName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
	TSubclassOf<AProjectileBase> AmmoClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
	int32 ClipSize;

	void SetClipCount(const int32 NewClip)
	{
		CurrentClip = FMath::Clamp<int32>(NewClip, 0, ClipSize);
	}

	int32 GetClipCount() const
	{
		return CurrentClip;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
	int32 CurrentClip;
};