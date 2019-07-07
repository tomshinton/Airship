// Airship Project - Tom Shinton 2018

#include "Healthbar.h"
#include "ProgressBar.h"
#include "HealthInterface.h"

namespace HealthbarAnims
{
	const FName Anim_Show("ShowAnim");
	const FName Anim_Hide("HideAnim");
}

UHealthbar::UHealthbar(const FObjectInitializer& ObjectInitializer)
	: UAirWidget(ObjectInitializer)
	, HealthBar(nullptr)
	, MaxHealth(100.f)
	, CurrentHealth(MaxHealth)
	, HealthInterface(nullptr)
	, HealthbarOnScreen(false)
{}

void UHealthbar::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (HealthBar)
	{
		HealthBar->SetPercent(GetHealthAsPercentage());
	} 
}

void UHealthbar::SetHealthInterface(IHealthInterface* InHealthInterface)
{
	if (InHealthInterface)
	{
		HealthInterface.SetObject(this);
		HealthInterface.SetInterface(InHealthInterface); 

		HealthInterface->GetOnHealthChangedEvent().AddLambda([this](const FBaseDamageEvent& InEvent)
		{
			UpdateBar(InEvent);
		});
	}
}

void UHealthbar::NativeConstruct()
{
	Super::NativeConstruct();

	if (HealthBar && HealthInterface)
	{
		HealthBar->SetPercent(GetHealthAsPercentage());
	}
}

float UHealthbar::GetHealthAsPercentage() const
{
	if (MaxHealth > 0.f)
	{
		const float NewPercentage = CurrentHealth / MaxHealth;
		return FMath::Clamp(NewPercentage, 0.f, 100.f);
	}

	return 0.f;
}

void UHealthbar::UpdateBar(const FBaseDamageEvent& InUpdateReason)
{
	if (!HealthbarOnScreen)
	{
		SetVisibility(ESlateVisibility::Visible);
		PlayAnimation(GetAnimationByName(HealthbarAnims::Anim_Show));

		HealthbarOnScreen = true;
	}

	CurrentHealth = HealthInterface->GetCurrentHealth();
	MaxHealth = HealthInterface->GetMaxHealth();

	HealthBar->SetPercent(GetHealthAsPercentage());
}
