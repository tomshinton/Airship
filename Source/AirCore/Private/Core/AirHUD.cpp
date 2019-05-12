// Fill out your copyright notice in the Description page of Project Settings.

#include "AirHUD.h"
#include "AirHUDBase.h"
#include "UISettings.h"
#include <UserWidget.h>
#include "AirHUDBase.h"

AAirHUD::AAirHUD(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{}

void AAirHUD::BeginPlay()
{
	if (UWorld* World = GetWorld())
	{
		if (UUISettings* UISettings = GetMutableDefault<UUISettings>())
		{
			if (UISettings->HUDWidget)
			{
				HUDWidget = CreateWidget<UAirHUDBase>(World, UISettings->HUDWidget);
				HUDWidget->SetupBinding(CachedInputComponent);
				HUDWidget->AddToViewport(0);
			}
		}
	}
}

void AAirHUD::CachePlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	CachedInputComponent = PlayerInputComponent;
}