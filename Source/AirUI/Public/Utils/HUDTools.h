// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "AirController.h"

namespace HUDTools
{
	bool IsVisible(const UUserWidget& InWidget)
	{
		return InWidget.GetVisibility() == ESlateVisibility::Visible;
	}

	void RequestMouseFocus(const AActor& WorldContext)
	{
		if (UWorld* World = WorldContext.GetWorld())
		{
			if (AAirController* LocalController = Cast<AAirController>(World->GetFirstPlayerController()))
			{
				LocalController->SetMouseVisible(true);
			}
		}
	}

	void ReleaseMouseFocus(const AActor& WorldContext)
	{
		if (UWorld* World = WorldContext.GetWorld())
		{
			if (AAirController* LocalController = Cast<AAirController>(World->GetFirstPlayerController()))
			{
				LocalController->SetMouseVisible(false);
			}
		}
	}

	bool IsMouseVisible(const AActor& WorldContext)
	{
		if (UWorld* World = WorldContext.GetWorld())
		{
			if (AAirController* LocalController = Cast<AAirController>(World->GetFirstPlayerController()))
			{
				return LocalController->GetMouseVisible();
			}
		}

		return false;
	}

}