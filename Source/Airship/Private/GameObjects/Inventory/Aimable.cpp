// Fill out your copyright notice in the Description page of Project Settings.

#include "Aimable.h"
#include <Kismet/GameplayStatics.h>
#include "AirHUD.h"
#include "AirInventory.h"

#include "WorldItem.h"

AAimable::AAimable()
{
	Scope = CreateDefaultSubobject<UScope>(TEXT("Scope"));
	Scope->SetupAttachment(RootComponent);
}

void AAimable::StartSecondary()
{
	if (AAirHUD* HUD = Cast<AAirHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD()))
	{
		HUD->SetIsAiming(true);
	}

	if (AssociatedInventoryComponent)
	{
		AssociatedInventoryComponent->SetIsAiming(true);
	}

	if (UseScope)
	{
		UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(this, BlendTime, EViewTargetBlendFunction::VTBlend_EaseInOut, BlendExp, false);
	}
}

void AAimable::EndSecondary()
{
	if (AAirHUD* HUD = Cast<AAirHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD()))
	{
		HUD->SetIsAiming(false);
	}

	if (AssociatedInventoryComponent)
	{
		AssociatedInventoryComponent->SetIsAiming(false);
	}

	if (UseScope)
	{
		AActor* OwningCharacter = reinterpret_cast<AActor*>(UGameplayStatics::GetPlayerCharacter(this, 0));
		UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(OwningCharacter, BlendTime, EViewTargetBlendFunction::VTBlend_EaseInOut, BlendExp, false);
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
