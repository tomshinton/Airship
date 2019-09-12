// Airship Project - Tom Shinton 2018

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

		if (FViewport* CurrentViewport = GetLocalPlayer()->ViewportClient->Viewport)
		{
			FVector2D ViewportSize;
			GetLocalPlayer()->ViewportClient->GetViewportSize(ViewportSize);

			const int32 X = (int32)(ViewportSize.X * 0.5f);
			const int32 Y = (int32)(ViewportSize.Y * 0.5f);
			CurrentViewport->SetMouse(X, Y);
		}
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
