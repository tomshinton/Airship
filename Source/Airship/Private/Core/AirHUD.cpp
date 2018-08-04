// Fill out your copyright notice in the Description page of Project Settings.

#include "AirHUD.h"
#include "ConstructorHelpers.h"
#include "AirWidget.h"
#include "Utils/Functions/UMGFunctions.h"
#include "AirController.h"
#include <Kismet/GameplayStatics.h>
#include <WidgetBlueprintLibrary.h>

AAirHUD::AAirHUD(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{}

void AAirHUD::BeginPlay()
{
	if (UWorld* World = GetWorld())
	{
		if (HUD)
		{
			HUDWidget = UUMGFunctions::CreateAirWidget(World, HUD);
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

void AAirHUD::ToggleInventoryScreen()
{
	if (UAirWidget* InventoryWidgetPtr = InventoryScreenWidget.Get())
	{
		if (UWorld* World = GetWorld())
		{
			if (AAirController* LocalController = Cast<AAirController>(UGameplayStatics::GetPlayerController(World, 0)))
			{
				if (InventoryWidgetPtr->IsInViewport())
				{
					InventoryWidgetPtr->RemoveFromParent();
					HUDWidget->SetUserFocus(LocalController);
					LocalController->bShowMouseCursor = false;
					UWidgetBlueprintLibrary::SetInputMode_GameOnly(LocalController);
				}
				else
				{
					InventoryWidgetPtr->AddToViewport(1);
					InventoryWidgetPtr->SetUserFocus(LocalController);
					InventoryWidgetPtr->SetKeyboardFocus();
					LocalController->bShowMouseCursor = true;
					UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(LocalController, InventoryWidgetPtr, EMouseLockMode::LockAlways);
				}
			}
		}
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

