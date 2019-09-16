// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/QuickTransfer/SlotDomain.h"

#include <Runtime/Engine/Classes/Engine/DataAsset.h>

class UTransferTargetBase;

#include "TransferRequestTargetDataAsset.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FTransferTarget
{
	GENERATED_BODY()

	FTransferTarget()
		: TransferTargets()
	{};

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UTransferTargetBase>> TransferTargets;
};

UCLASS(Blueprintable, BlueprintType)
class UTransferRequestTargetDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TMap<ESlotDomain, FTransferTarget> Targets;
};