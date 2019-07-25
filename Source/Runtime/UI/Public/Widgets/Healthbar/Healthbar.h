// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/AirWidget.h"

#include <AirCore/Public/Interfaces/HealthInterface.h>
#include <AirCore/Utils/Events/HealthEvents.h>

#include "Healthbar.generated.h"

class UHealthComponent;
class UProgressBar;

//////////////////////////////////////////////////////////////////////////
// Base class for all healthbars
//////////////////////////////////////////////////////////////////////////

UCLASS()
class UHealthbar : public UAirWidget
{
	GENERATED_BODY()

public:

	UHealthbar(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(EditAnywhere, Category = Health)
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = Health)
	float CurrentHealth;

	virtual void SynchronizeProperties() override;

	void SetHealthInterface(IHealthInterface* InHealthComponent);;

protected:
	
	virtual void NativeConstruct() override;

private:

	TScriptInterface<IHealthInterface> HealthInterface;

	bool HealthbarOnScreen;

	float TimeUntilBarHidden;

	FTimerHandle HideBarTimerHandle;

	float GetHealthAsPercentage() const;

	void UpdateBar(const FHealthChangeEvent& InUpdateReason);
};
