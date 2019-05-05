// Fill out your copyright notice in the Description page of Project Settings.

#include "AirHUDBase.h"
#include "AirWidget.h"
#include <CanvasPanel.h>

void UAirHUDBase::Build()
{
	Super::Build();
}

void UAirHUDBase::AddInventoryWidgetToPanel(UUserWidget* InWidget)
{
	if (InventoryPanel)
	{
		InventoryPanel->ClearChildren();

		if (InWidget)
		{
			InventoryPanel->AddChild(InWidget);
		}
	}
}

void UAirHUDBase::RemoveInventoryWidgetFromPanel()
{
	if (InventoryPanel)
	{
		InventoryPanel->ClearChildren();
	}
}

bool UAirHUDBase::IsInventoryPanelPopulated() const
{
	if (InventoryPanel)
	{
		if (InventoryPanel->GetChildrenCount() > 0)
		{
			return true;
		}
	}

	return false;
}

void UAirHUDBase::SetInventoryPanelVisiblity(const ESlateVisibility InNewVisibility)
{
	InventoryPanel->SetVisibility(InNewVisibility);
}