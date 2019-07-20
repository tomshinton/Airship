// Fill out your copyright notice in the Description page of Project Settings.

#include "AirHUDBase.h"
#include "InventoryPanel.h"
#include "Healthbar.h"
#include "ComponentProviderInterface.h"
#include "AirChar.h"
#include "HealthComponent.h"
#include "HUDTools.h"
#include "InteractionInterface.h"
#include "Utils/Functions/InterfaceHelpers.h"
#include "HealthInterface.h"
#include "InspectorPanel.h"

UAirHUDBase::UAirHUDBase(const FObjectInitializer& ObjectInitializer)
	: UAirWidget(ObjectInitializer)
	, Hotbar(nullptr)
	, PlayerInventoryPanel(nullptr)
	, PlayerHealthBar(nullptr)
	, InspectorPanel(nullptr)
{

}

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
			if (IHealthInterface* HealthInterface = InterfaceHelpers::GetInterface<IHealthInterface>(*LocalChar))
			{
				PlayerHealthBar->SetHealthInterface(HealthInterface);
				PlayerHealthBar->SetVisibility(ESlateVisibility::Collapsed);
			}
		}

		if (InspectorPanel)
		{
			if (IInteractionInterface* InteractionInterface = InterfaceHelpers::GetInterface<IInteractionInterface>(*LocalChar->GetController()))
			{
				InspectorPanel->SetInteractionInterface(InteractionInterface);
				InspectorPanel->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}

void UAirHUDBase::ToggleInventoryPanel()
{
	/*if (UHUDTools::IsVisible(*PlayerInventoryPanel))
	{
		PlayerInventoryPanel->SetVisibility(ESlateVisibility::Collapsed);
		UHUDTools::ReleaseMouseFocus(*LocalChar);
	}
	else
	{
		PlayerInventoryPanel->SetVisibility(ESlateVisibility::Visible);
		UHUDTools::RequestMouseFocus(*LocalChar);
	}*/
}

void UAirHUDBase::SetupBinding(UInputComponent* InInputComponent)
{
	if (InInputComponent)
	{
		InInputComponent->BindAction("ToggleInventoryPanel", IE_Pressed, this, &UAirHUDBase::ToggleInventoryPanel);
	}
}
