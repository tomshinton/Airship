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
	if (UAirHUDBase* HUDWidgetPtr = HUDWidget.Get())
	{
		if (AAirController* LocalController = Cast<AAirController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			HUDWidgetPtr->RemoveInventoryWidgetFromPanel();
			HUDWidgetPtr->SetUserFocus(LocalController);
			LocalController->bShowMouseCursor = false;
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(LocalController);
		}
	}
}

void AAirHUD::ToggleInventoryScreen()
{
	if (UAirHUDBase* HUDWidgetPtr = HUDWidget.Get())
	{
		if (UWorld* World = GetWorld())
		{
			if (AAirController* LocalController = Cast<AAirController>(UGameplayStatics::GetPlayerController(World, 0)))
			{
				if (HUDWidgetPtr->IsInventoryPanelPopulated())
				{
					ClearInventoryPanel();	
				}
				else if (UAirWidget* InventoryWidgetPtr = InventoryScreenWidget.Get())
				{
					AddInventoryScreen(InventoryWidgetPtr, LocalController);
				}
			}
		}
	}
}

void AAirHUD::AddInventoryScreen(UUserWidget* InNewInventoryScreen, AAirController* InController)
{
	if (UAirHUDBase* HUDWidgetPtr = HUDWidget.Get())
	{
		if (HUDWidgetPtr->IsInventoryPanelPopulated())
		{
			ClearInventoryPanel();
		}

		HUDWidgetPtr->AddInventoryWidgetToPanel(InNewInventoryScreen);
		
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

	if (CrosshairWidget.Get())
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

