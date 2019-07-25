#pragma once

#include "WieldInterface.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UWieldInterface : public UInterface
{
	GENERATED_BODY()
};

class WIELDING_API IWieldInterface
{
	GENERATED_BODY()

public:

	virtual void StartPrimary() = 0;
	virtual void EndPrimary() = 0;

	virtual void StartSecondary() = 0;
	virtual void EndSecondary() = 0;

	virtual void StartWield() = 0;
	virtual void EndWield() = 0;
};
