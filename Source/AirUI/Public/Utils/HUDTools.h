// Airship Project - Tom Shinton 2018

#pragma once
#include "Engine/World.h"
#include "AirController.h"

#include "UserWidget.h"
#include "CanvasPanel.h"
#include "AirHUDBase.h"

#include "HUDTools.generated.h"

UCLASS(MinimalAPI)
class UHUDTools : public UObject
{
	GENERATED_BODY()

	UHUDTools() {};

public:

	AIRUI_API static bool IsVisible(const UUserWidget& InWidget)
	{
		return InWidget.GetVisibility() == ESlateVisibility::Visible;
	};

	AIRUI_API static void RequestMouseFocus(const AActor& WorldContext)
	{
		if (UWorld* World = WorldContext.GetWorld())
		{
			if (AAirController* LocalController = Cast<AAirController>(World->GetFirstPlayerController()))
			{
				LocalController->SetMouseVisible(true);
			}
		}
	};

	AIRUI_API static void ReleaseMouseFocus(const AActor& WorldContext)
	{
		if (UWorld* World = WorldContext.GetWorld())
		{
			if (AAirController* LocalController = Cast<AAirController>(World->GetFirstPlayerController()))
			{
				LocalController->SetMouseVisible(false);
			}
		}
	};

	AIRUI_API static bool IsMouseVisible(const AActor& WorldContext)
	{
		if (UWorld* World = WorldContext.GetWorld())
		{
			if (AAirController* LocalController = Cast<AAirController>(World->GetFirstPlayerController()))
			{
				return LocalController->GetMouseVisible();
			}
		}

		return false;
	};

	AIRUI_API static UCanvasPanel* GetDynamicPanel(const AActor& WorldContext)
	{
		if (UWorld* World = WorldContext.GetWorld())
		{
			if (AAirController* LocalController = Cast<AAirController>(World->GetFirstPlayerController()))
			{
				if (UAirHUDBase* HudWidget = LocalController->GetHudWidget())
				{
					return HudWidget->DynamicPanel;
				}
			}
		}

		return nullptr;
	};
};