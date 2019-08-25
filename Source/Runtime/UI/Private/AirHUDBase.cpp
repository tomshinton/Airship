// Airship Project - Tom Shinton 2018

#include "Runtime/UI/Public/AirHUDBase.h"

#include "Runtime/UI/Public/Utils/HUDTools.h"
#include "Runtime/UI/Public/Widgets/Healthbar/Healthbar.h"
#include "Runtime/UI/Public/Widgets/Hotbar/Hotbar.h"
#include "Runtime/UI/Public/Widgets/InspectorPanel/InspectorPanel.h"
#include "Runtime/UI/Public/Widgets/Inventory/InventoryPanel.h"
#include "Runtime/UI/Public/Widgets/Inventory/InventoryViewInterface.h"

#include <AirCore/Utils/Functions/InterfaceHelpers.h>
#include <AirCore/Public/Core/AirChar.h>
#include <AirCore/Public/Interfaces/HealthInterface.h>
#include <AirCore/Public/Interfaces/InteractionInterface.h>
#include <Runtime/Inventory/Public/InventoryInterface.h>
#include <Runtime/UMG/Public/Blueprint/WidgetTree.h>
#include <Runtime/UMG/Public/Components/Overlay.h>
#include <Runtime/UMG/Public/Components/Widget.h>

UAirHUDBase::UAirHUDBase(const FObjectInitializer& ObjectInitializer)
	: UAirWidget(ObjectInitializer)
	, Hotbar(nullptr)
	, PlayerInventoryPanel(nullptr)
	, PlayerHealthBar(nullptr)
	, InspectorPanel(nullptr)
	, DraggableAction(new FDraggableAction(*this))
{}

void UAirHUDBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (LocalChar)
	{
		if (PlayerInventoryPanel)
		{
			if (IInventoryInterface* InventoryInterface = InterfaceHelpers::GetInterface<IInventoryInterface>(*LocalChar))
			{
				if (IInventoryViewInterface* InventoryViewInterface = Cast<IInventoryViewInterface>(PlayerInventoryPanel))
				{
					InventoryViewInterface->SetLinkedInventory(InventoryInterface);
				}
			}

			PlayerInventoryPanel->Build();
			PlayerInventoryPanel->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (PlayerHealthBar)
		{
			if (IHealthInterface* HealthInterface = InterfaceHelpers::GetInterface<IHealthInterface>(*LocalChar))
			{
				PlayerHealthBar->SetHealthInterface(HealthInterface);
				PlayerHealthBar->Build();
				PlayerHealthBar->SetVisibility(ESlateVisibility::Collapsed);
			}
		}

		if (InspectorPanel)
		{
			if (IInteractionInterface* InteractionInterface = InterfaceHelpers::GetInterface<IInteractionInterface>(*LocalChar->GetController()))
			{
				InspectorPanel->SetInteractionInterface(InteractionInterface);
				InspectorPanel->Build();

				InspectorPanel->SetVisibility(ESlateVisibility::Collapsed);
			}
		}

		if (Hotbar)
		{
			if (IInventoryInterface* InventoryInterface = InterfaceHelpers::GetInterface<IInventoryInterface>(*LocalChar))
			{
				if (IHotbarInterface* HotbarInterface = InterfaceHelpers::GetInterface<IHotbarInterface>(*LocalChar))
				{
					if (IInventoryViewInterface* InventoryViewInterface = Cast<IInventoryViewInterface>(Hotbar))
					{
						InventoryViewInterface->SetLinkedInventory(InventoryInterface);
						InventoryViewInterface->SetLinkedHotbar(HotbarInterface);
						Hotbar->Build();
					}
				}
			}
		}
	}
}

bool UAirHUDBase::ShouldBeSnapshot(const UWidget& InWidget, const UWidgetTree& InWidgetTree, const UDynamicOverlayPanel& InOverlay)
{
	return &InWidget != &InOverlay && &InWidget != InWidgetTree.RootWidget && !InOverlay.GetAllChildren().Contains(&InWidget);
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
		if (ShouldBeSnapshot(*Widget, *WidgetTree, *DynamicOverlay))
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

		DraggableAction->Init(*InInputComponent);
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
