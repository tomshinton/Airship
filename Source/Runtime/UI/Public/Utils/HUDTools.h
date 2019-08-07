// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/AirWidget.h"
#include "Runtime/UI/Public/AirHUDBase.h"

#include <AirCore/Public/Core/AirController.h>
#include <Runtime/Engine/Classes/Engine/World.h>
#include <Runtime/UMG/Public/Components/CanvasPanel.h>
#include <Runtime/UI/Public/Elements/DynamicOverlayPanel.h>
#include <Runtime/UMG/Public/Components/OverlaySlot.h>

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

	UI_API static UDynamicOverlayPanel& GetDynamicPanel(const AActor& WorldContext)
	{
		UDynamicOverlayPanel* FoundOverlay = nullptr;
		
		if (UAirHUDBase* HudWidget = &GetHUDWidget(WorldContext))
		{
			FoundOverlay = HudWidget->DynamicOverlay;
		}
		
		return *FoundOverlay;
	};
	   
	UI_API static void AddToDynamicPanel(UUserWidget* InWidget, const AActor& WorldContext)
	{
		UDynamicOverlayPanel& DynamicPanel = GetDynamicPanel(WorldContext);

		if (!DynamicPanel.GetIsLocked())
		{
			if (UPanelSlot* AddedChild = DynamicPanel.AddChild(InWidget))
			{
				if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(AddedChild))
				{
					OverlaySlot->SetHorizontalAlignment(HAlign_Fill);
					OverlaySlot->SetVerticalAlignment(VAlign_Fill);

					GetHUDWidget(WorldContext).OnDynamicPanelUpdated();

					if (UAirWidget* AirWidget = Cast<UAirWidget>(InWidget))
					{
						AirWidget->Build();
					}
				}
			}
		}
	}
};