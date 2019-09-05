// Airship Project - Tom Shinton 2018

#include "Runtime/Item/Public/Aimable.h"
#include "Runtime/Item/Public/Scope.h"

#include <AirCore/Public/Core/AirHUD.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/Inventory/Public/InventoryComponent/AirInventory.h>
#include <Runtime/Projectile/Public/ProjectileBase.h>

const float AAimable::MaxFireDistance = 50000.f;

AAimable::AAimable()
	: Scope(CreateDefaultSubobject<UScope>(TEXT("Scope")))
{
	Scope->SetupAttachment(RootComponent);
}

void AAimable::StartSecondary()
{
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

FVector AAimable::GetFireDirection() const
{
	if (AssociatedInventoryComponent->GetIsAiming())
	{
		if (UWorld* World = GetWorld())
		{
			if (APlayerController* PlayerController = World->GetFirstPlayerController())
			{
				if (Scope)
				{
					const FVector WorldLocation = Scope->GetComponentLocation();
					const FVector WorldDirection = Scope->GetForwardVector();
					const FVector AimEnd = WorldLocation + (WorldDirection * MaxFireDistance);
					const FVector AimStart = GetBarrelTransform().GetValue().GetLocation();

					return (AimEnd - AimStart).GetSafeNormal();
				}
			}
		}
	}
	else
	{
		if (GetBarrelTransform().IsSet())
		{
			const FRotator BarrelRotation = GetBarrelTransform().GetValue().Rotator();
			return BarrelRotation.Vector().GetSafeNormal();
		}
	}

	return GetActorRotation().Vector().GetSafeNormal();
}

void AAimable::StartPrimary()
{
	if(IsFirable)
	{
		StartFire();
	}
}

void AAimable::EndPrimary()
{
	if (IsFirable && HasFired)
	{
		EndFire();
	}
}

void AAimable::StartFire()
{

}

void AAimable::EndFire()
{

}
