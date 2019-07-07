// Fill out your copyright notice in the Description page of Project Settings.

#include "AirHUDBase.h"
#include "InventoryPanel.h"
#include "Healthbar.h"
#include "ComponentProviderInterface.h"
#include "AirChar.h"
#include "HealthComponent.h"

void UAirHUDBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (LocalChar)
	{
		if (PlayerInventoryPanel)
		{
			PlayerInventoryPanel->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (PlayerHealthBar)
		{
			if (IComponentProviderInterface* CompProvider = Cast<IComponentProviderInterface>(LocalChar))
			{
				PlayerHealthBar->SetHealthInterface(Cast<IHealthInterface>(CompProvider->GetHealthComponent()));
				PlayerHealthBar->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}

void UAirHUDBase::SetupBinding(UInputComponent* InInputComponent)
{
	if (InInputComponent)
	{
		//Add default bindings here for all main HUD actions
	}
}
