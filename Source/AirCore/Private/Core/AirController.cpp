// Fill out your copyright notice in the Description page of Project Settings.

#include "AirController.h"
#include "InteractionComponent.h"
#include "AirCheatManager.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Engine.h"
#include "AirHUD.h"
#include "AirHUDBase.h"

namespace
{
	namespace AirControllerPrivate
	{
		const FName InteractionComponentName = TEXT("InteractionComponent");
	}
}

AAirController::AAirController()
	: InteractionComponent(CreateDefaultSubobject<UInteractionComponent>(AirControllerPrivate::InteractionComponentName))
	, MouseVisible(false)
{
	CheatClass = UAirCheatManager::StaticClass();
}

void AAirController::SetMouseVisible(const bool InVisibility)
{
	bShowMouseCursor = InVisibility;
	bEnableClickEvents = InVisibility;
	bEnableMouseOverEvents = InVisibility;

	MouseVisible = InVisibility;

	if (InVisibility)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		InputMode.SetHideCursorDuringCapture(false);

		InputMode.SetWidgetToFocus(GetHudWidget()->TakeWidget());
		SetInputMode(InputMode);
	}
	else
	{
		FInputModeGameOnly InputMode;
		
		SetInputMode(InputMode);
	}
}

bool AAirController::GetMouseVisible() const
{
	return MouseVisible;
}

UAirHUDBase* AAirController::GetHudWidget() const
{
	if (AAirHUD* AirHud = Cast <AAirHUD>(GetHUD()))
	{
		return AirHud->GetHUDWidget();
	}

	return nullptr;
}
