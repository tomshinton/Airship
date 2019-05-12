// Fill out your copyright notice in the Description page of Project Settings.

#include "AirHUDBase.h"
#include "InventoryPanel.h"
#include <Engine/Engine.h>

void UAirHUDBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayerInventoryPanel)
	{
		PlayerInventoryPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UAirHUDBase::SetupBinding(UInputComponent* InInputComponent)
{
	if (InInputComponent)
	{
		//Add default bindings here for all main HUD actions
	}
}
