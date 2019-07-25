// Airship Project - Tom Shinton 2018

#pragma once
#include "Engine/World.h"
#include "AirController.h"

#include "UserWidget.h"
#include "CanvasPanel.h"
#include "AirHUDBase.h"
#include "Overlay.h"
#include "OverlaySlot.h"

#include "HUDTools.generated.h"

UCLASS(MinimalAPI)
class UHUDTools : public UObject
{
	GENERATED_BODY()

	UHUDTools() {};

public:

	UI_API static UAirHUDBase& GetHUDWidget(const AActor& WorldContext)
	{
		UAirHUDBase* FoundWidget = nullptr;

		if (UWorld* World = WorldContext.GetWorld())
		{
			if (AAirController* LocalController = Cast<AAirController>(World->GetFirstPlayerController()))
			{
				if (UAirHUDBase* HUDWidget = LocalController->GetHudWidget())
				{
					FoundWidget = HUDWidget;
				}
			}
		}

		return *FoundWidget;
	}

	UI_API static bool IsVisible(const UUserWidget& InWidget)
	{
		return InWidget.GetVisibility() == ESlateVisibility::Visible;
	};

	UI_API static void RequestMouseFocus(const AActor& WorldContext)
	{
		if (UWorld* World = WorldContext.GetWorld())
		{
			if (AAirController* LocalController = Cast<AAirController>(World->GetFirstPlayerController()))
			{
				LocalController->SetMouseVisible(true);
			}
		}
	};

	UI_API static void ReleaseMouseFocus(const AActor& WorldContext)
	{
		if (UWorld* World = WorldContext.GetWorld())
		{
			if (AAirController* LocalController = Cast<AAirController>(World->GetFirstPlayerController()))
			{
				LocalController->SetMouseVisible(false);
			}
		}
	};

	UI_API static bool IsMouseVisible(const AActor& WorldContext)
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

	UI_API static UOverlay& GetDynamicPanel(const AActor& WorldContext)
	{
		UOverlay* FoundOverlay = nullptr;
		
		if (UAirHUDBase* HudWidget = &GetHUDWidget(WorldContext))
		{
			FoundOverlay = HudWidget->DynamicOverlay;
		}
		
		return *FoundOverlay;
	};



	UI_API static void AddToDynamicPanel(UUserWidget* InWidget, const AActor& WorldContext)
	{
		UOverlay& DynamicPanel = GetDynamicPanel(WorldContext);

		if (UPanelSlot* AddedChild = DynamicPanel.AddChild(InWidget))
		{
			if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(AddedChild))
			{
				OverlaySlot->SetHorizontalAlignment(HAlign_Fill);
				OverlaySlot->SetVerticalAlignment(VAlign_Fill);

				GetHUDWidget(WorldContext).OnDynamicPanelUpdated();
			}
		}
	}
};