// Fill out your copyright notice in the Description page of Project Settings.

#include "Aimable.h"
#include <Kismet/GameplayStatics.h>
#include "AirHUD.h"

void AAimable::StartSecondary()
{
	if (AAirHUD* HUD = Cast<AAirHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD()))
	{
		HUD->SetIsAiming(true);
	}
}

void AAimable::EndSecondary()
{
	if (AAirHUD* HUD = Cast<AAirHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD()))
	{
		HUD->SetIsAiming(false);
	}
}

void AAimable::StartPrimary()
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::White, "Aimable start primary");
}

void AAimable::EndPrimary()
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::White, "Aimable end primary");
}
