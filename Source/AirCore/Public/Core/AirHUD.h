// Airship Project - Tom Shinton 2018

#pragma once

#include "GameFramework/HUD.h"
#include "AirHUD.generated.h"

class UAirHUDBase;
class UInputComponent;

UCLASS(MinimalAPI)
class AAirHUD : public AHUD
{
	GENERATED_BODY()

	AAirHUD(const FObjectInitializer& ObjectInitializer);

public:
	void CachePlayerInputComponent(UInputComponent* PlayerInputComponent);

	UAirHUDBase* GetHUDWidget() const { return HUDWidget; };

protected:

	virtual void BeginPlay() override;

	UPROPERTY()
	UAirHUDBase* HUDWidget;

	UPROPERTY()
	UInputComponent* CachedInputComponent;
};
