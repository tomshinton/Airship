// Airship Project - Tom Shinton 2018

#include "Healthbar.h"
#include "ProgressBar.h"
#include "HealthInterface.h"
#include "TimerManager.h"

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
	, TimeUntilBarHidden(2.f)
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

		HealthInterface->GetOnHealthChangedEvent().AddLambda([this](const FHealthChangeEvent& InEvent)
		{
			UpdateBar(InEvent);
		});

		HealthInterface->GetOnHealthRestoredEvent().AddLambda([this]()
		{
			if (UWorld* World = GetWorld())
			{
				FTimerDelegate HideDelegate;
				HideDelegate.BindLambda([this]()
				{
					PlayAnimation(HideAnim);
					HealthbarOnScreen = false;
				});

				World->GetTimerManager().SetTimer(HideBarTimerHandle, HideDelegate, TimeUntilBarHidden, false, TimeUntilBarHidden);
			}
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

void UHealthbar::UpdateBar(const FHealthChangeEvent& InUpdateReason)
{
	if (!HealthbarOnScreen)
	{
		SetVisibility(ESlateVisibility::Visible);
		PlayAnimation(ShowAnim);

		HealthbarOnScreen = true;
	}

	CurrentHealth = HealthInterface->GetCurrentHealth();
	MaxHealth = HealthInterface->GetMaxHealth();

	HealthBar->SetPercent(GetHealthAsPercentage());
}