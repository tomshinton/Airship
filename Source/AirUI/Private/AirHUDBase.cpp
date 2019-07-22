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
#include "UserWidget.h"
#include "WidgetTree.h"

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

bool UAirHUDBase::ShouldBeSnapshot(UWidget* InWidget, UWidgetTree* InWidgetTree, UOverlay* InOverlay)
{
	return InWidget != InOverlay && InWidget != InWidgetTree->RootWidget && !InOverlay->GetAllChildren().Contains(InWidget);
}

void UAirHUDBase::ToggleInventoryPanel()
{
	if (!TryRemoveTopLevelDynamicWidget())
	{
		if (UHUDTools::IsVisible(*PlayerInventoryPanel))
		{
			PlayerInventoryPanel->SetVisibility(ESlateVisibility::Collapsed);
			UHUDTools::ReleaseMouseFocus(*LocalChar);
		}
		else
		{
			PlayerInventoryPanel->SetVisibility(ESlateVisibility::Visible);
			UHUDTools::RequestMouseFocus(*LocalChar);
		}
	}
}

void UAirHUDBase::TakeSnapshot()
{
	Snapshot.Empty();

	TArray<UWidget*> FoundWidgets;
	WidgetTree->GetAllWidgets(FoundWidgets);

	for (UWidget* Widget : FoundWidgets)
	{
		if (ShouldBeSnapshot(Widget, WidgetTree, DynamicOverlay))
		{
			Snapshot.Add(Widget, Widget->GetVisibility());
			Widget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UAirHUDBase::RestoreSnapshot()
{
	for (TPair<UWidget*, ESlateVisibility> SnapshotEntry : Snapshot)
	{
		SnapshotEntry.Key->SetVisibility(SnapshotEntry.Value);
	}

	Snapshot.Empty();
}

bool UAirHUDBase::TryRemoveTopLevelDynamicWidget()
{
	TArray<UWidget*> FoundWidgets = DynamicOverlay->GetAllChildren();
	
	if (FoundWidgets.Num() > 0)
	{
		FoundWidgets[0]->RemoveFromParent();
		OnDynamicPanelUpdated();
		return true;
	}

	return false;
}

void UAirHUDBase::SetupBinding(UInputComponent* InInputComponent)
{
	if (InInputComponent)
	{
		InInputComponent->BindAction("ToggleInventoryPanel", IE_Pressed, this, &UAirHUDBase::ToggleInventoryPanel);
	}
}

void UAirHUDBase::OnDynamicPanelUpdated()
{
	TArray<UWidget*> FoundWidgets = DynamicOverlay->GetAllChildren();

	if (FoundWidgets.Num() > 0 && Snapshot.Num() == 0)
	{
		TakeSnapshot();
		UHUDTools::RequestMouseFocus(*LocalChar);
	}
	else
	{
		RestoreSnapshot();
		UHUDTools::ReleaseMouseFocus(*LocalChar);
	}
}
