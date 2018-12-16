// Fill out your copyright notice in the Description page of Project Settings.

#include "AirHUD.h"
#include "ConstructorHelpers.h"
#include "AirWidget.h"
#include "Utils/Functions/UMGFunctions.h"
#include "AirController.h"
#include <Kismet/GameplayStatics.h>
#include <WidgetBlueprintLibrary.h>
#include "AirHUDBase.h"
#include <CanvasPanelSlot.h>
#include <WidgetLayoutLibrary.h>

AAirHUD::AAirHUD(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{}

void AAirHUD::BeginPlay()
{
	if (UWorld* World = GetWorld())
	{
		if (HUD)
		{
			HUDWidget = Cast<UAirHUDBase>(UUMGFunctions::CreateAirWidget(World, HUD));
			HUDWidget->SetOwningHUD(this);

			HUDWidget->AddToViewport(-1);
		}

		if (InventoryScreen)
		{
			InventoryScreenWidget = UUMGFunctions::CreateAirWidget(World, InventoryScreen);
			InventoryScreenWidget->SetOwningHUD(this);
		}

		if (Crosshair)
		{
			CrosshairWidget = CreateWidget<UUserWidget>(World, Crosshair);
		}
	}
}

void AAirHUD::ClearInventoryPanel()
{
	if (HUDWidget)
	{
		if (AAirController* LocalController = Cast<AAirController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			HUDWidget->RemoveInventoryWidgetFromPanel();
			HUDWidget->SetUserFocus(LocalController);
			LocalController->bShowMouseCursor = false;
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(LocalController);
		}
	}
}

void AAirHUD::ToggleInventoryScreen()
{
	if (HUDWidget)
	{
		if (UWorld* World = GetWorld())
		{
			if (AAirController* LocalController = Cast<AAirController>(UGameplayStatics::GetPlayerController(World, 0)))
			{
				if (HUDWidget->IsInventoryPanelPopulated())
				{
					ClearInventoryPanel();	
				}
				else if (InventoryScreenWidget)
				{
					AddInventoryScreen(InventoryScreenWidget, LocalController);
				}
			}
		}
	}
}

void AAirHUD::AddInventoryScreen(UUserWidget* InNewInventoryScreen, AAirController* InController)
{
	if (HUDWidget)
	{
		if (HUDWidget->IsInventoryPanelPopulated())
		{
			ClearInventoryPanel();
		}

		HUDWidget->AddInventoryWidgetToPanel(InNewInventoryScreen);
		
		if (UCanvasPanelSlot* InventoryAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InNewInventoryScreen))
		{
			InventoryAsCanvasSlot->SetAutoSize(true);

			InventoryAsCanvasSlot->SetAnchors(FAnchors(0,0,1, 1));
			InventoryAsCanvasSlot->SetOffsets(FMargin(0, 0, 0, 0));
		}

		InNewInventoryScreen->SetUserFocus(InController);
		InNewInventoryScreen->SetKeyboardFocus();
		InController->bShowMouseCursor = true;
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(InController, InNewInventoryScreen, EMouseLockMode::LockAlways);
	}
}

void AAirHUD::SetIsAiming(const bool InIsAiming)
{
	IsAiming = InIsAiming;

	if (CrosshairWidget)
	{
		if (IsAiming)
		{
			CrosshairWidget->AddToViewport(10);
		}
		else
		{
			CrosshairWidget->RemoveFromParent();
		}
	}
}

void AAirHUD::ReturnControlToHUD() const
{
	if (AAirController* LocalController = Cast<AAirController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		HUDWidget->SetUserFocus(LocalController);
		LocalController->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(LocalController);
	}
}

