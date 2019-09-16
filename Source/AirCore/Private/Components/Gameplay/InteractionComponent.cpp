// Airship Project - Tom Shinton 2018

#include "AirCore/Public/Components/Gameplay/InteractionComponent.h"
#include "AirCore/Public/Core/AirChar.h"
#include "AirCore/Public/Core/AirController.h"
#include "AirCore/Public/Interfaces/InteractableInterface.h"
#include "AirCore/Public/Interfaces/InteractionInterface.h"

#include <Runtime/Engine/Classes/Camera/CameraComponent.h>
#include <Runtime/Engine/Classes/Components/InputComponent.h>
#include <Runtime/Utils/Public/Collision/CollisionDefs.h>
#include <Runtime/Utils/Public/Interface/InterfaceHelpers.h>

#if !UE_BUILD_SHIPPING
#include <Runtime/Engine/Public/DrawDebugHelpers.h>
#endif //!UE_BUILD_SHIPPIONG

DEFINE_LOG_CATEGORY_STATIC(InteractionComponentLog, Log, Log);

UInteractionComponent::UInteractionComponent()
	: HoveredInteractable(nullptr)
	, CachedOwningPawn(nullptr)
	, IsAlreadyProcessingLook(false)
	, CachedTraceParams(FCollisionQueryParams())
	, OnLookOverDelegate()
	, CachedWorld(nullptr)
	, LookAtFrequency(1.f / 15.f) // About once every 15fps
	, LookAtDistance(10000.f)
	, LookAtTimerHandle()
	, FlatRefreshTime(1.f)
	, CurrentTraceCooldown(FlatRefreshTime)
	, LastKnownOwnerTransform(FTransform(NoInit))
	, OnNewItemHovered()
{}

void UInteractionComponent::BeginPlay()
{
	if (AAirController* OwningController = Cast<AAirController>(GetOwner()))
	{
		SetupInput(OwningController->GetPawn());

		CachedWorld = OwningController->GetWorld();

		BuildCachedTraceParams();
		EnableTick();
	}

	Super::BeginPlay();
}

FOnNewItemHovered& UInteractionComponent::GetOnNewItemHoveredDelegate()
{
	return OnNewItemHovered;
}

void UInteractionComponent::SetupInput(APawn* InNewPawn)
{
	if (AAirChar* OwningPawn = Cast<AAirChar>(InNewPawn))
	{
		CachedOwningPawn = OwningPawn;

		if (UInputComponent* CachedInputComponent = CachedOwningPawn->GetCachedInputComponent())
		{
			UE_LOG(InteractionComponentLog, Log, TEXT("Setting up Interaction bindings"));

			CachedInputComponent->BindAction("Interact", IE_Pressed, this, &UInteractionComponent::StartInteraction);
			CachedInputComponent->BindAction("Interact", IE_Released, this, &UInteractionComponent::EndInteraction);
		}
	}
}

void UInteractionComponent::EnableTick()
{
	if (CachedWorld)
	{
		FTimerManager& TimerManager = CachedWorld->GetTimerManager();
		TimerManager.SetTimer(LookAtTimerHandle, this, &UInteractionComponent::Look, LookAtFrequency, true, LookAtFrequency);
	}
}

void UInteractionComponent::BuildCachedTraceParams()
{
	const FName TraceTag = "LookAt";

	CachedTraceParams.AddIgnoredActor(CachedOwningPawn);
	CachedTraceParams.bTraceComplex = false;
	CachedTraceParams.TraceTag = TraceTag;

	OnLookOverDelegate.BindLambda([this](const FTraceHandle& InTraceHandle, FTraceDatum& InTraceDate)
	{
		OnLookOver(InTraceDate.OutHits);
	});
}

void UInteractionComponent::GetCurrentViewTargetInfo(FViewTargetInfo& OutLookAtInfo) const
{
	if (CachedOwningPawn)
	{
		if (AController* CurrentController = CachedOwningPawn->GetController())
		{
			AActor* FoundViewTarget = CurrentController->GetViewTarget();

			if (UActorComponent* ViewTargetCameraComponent = FoundViewTarget->GetComponentByClass(UCameraComponent::StaticClass()))
			{
				UCameraComponent* ViewTargetAsCamera = Cast<UCameraComponent>(ViewTargetCameraComponent);
				OutLookAtInfo.Set(ViewTargetAsCamera->GetComponentLocation(), ViewTargetAsCamera->GetComponentRotation());
				return;
			}

			OutLookAtInfo.Set(FoundViewTarget->GetActorLocation(), FoundViewTarget->GetActorRotation());
		}
	}
}

bool UInteractionComponent::ShouldTrace() const
{
	if (!LastKnownOwnerTransform.IsSet())
	{
		return true;
	}

	return FMath::IsNearlyZero(CurrentTraceCooldown) || !GetCurrentOwnerTransform().Equals(LastKnownOwnerTransform.GetValue());
}

FTransform UInteractionComponent::GetCurrentOwnerTransform() const
{
	if (CachedOwningPawn)
	{
		return CachedOwningPawn->GetTransform();
	}

	return FTransform();
}

void UInteractionComponent::SetLastKnownTransform()
{
	LastKnownOwnerTransform = CachedOwningPawn->GetTransform();
}

void UInteractionComponent::Look()
{
	FViewTargetInfo NewLookAtCache(LookAtDistance);
	GetCurrentViewTargetInfo(NewLookAtCache);

	if (CachedWorld && !IsAlreadyProcessingLook)
	{
		if (ShouldTrace())
		{
			CurrentTraceCooldown = FlatRefreshTime;

			if (GEngine)
			{
				CachedWorld->AsyncLineTraceByChannel(EAsyncTraceType::Single, NewLookAtCache.ViewStart, NewLookAtCache.ViewEnd, CC_LOOKANDUSE, CachedTraceParams, FCollisionResponseParams(), &OnLookOverDelegate);
				IsAlreadyProcessingLook = true;
			}
		}
		else
		{
			CurrentTraceCooldown = FMath::Clamp(CurrentTraceCooldown - LookAtFrequency, 0.f, FlatRefreshTime);
		}
	}
}

void UInteractionComponent::OnLookOver(const TArray<FHitResult>& InHits)
{
	//We only do a line trace, so if we're getting anything greater than 1 one, something's gone pearshaped.
	if (InHits.Num() > 0)
	{
		//Iterate through stack until we hit the first InteractableInterface
		for (const FHitResult& Hit : InHits)
		{
			if (AActor* FirstHit = Hit.Actor.Get())
			{
				if (IInteractableInterface* HitInteractableInterface = InterfaceHelpers::GetInterface<IInteractableInterface>(*FirstHit))
				{
					if (HoveredInteractable != HitInteractableInterface)
					{
						HoveredInteractable.SetObject(FirstHit);
						HoveredInteractable.SetInterface(HitInteractableInterface);

#if !UE_BUILD_SHIPPING
						UE_LOG(InteractionComponentLog, Log, TEXT("Caching %s for interactions"), *FirstHit->GetName());
#endif //!UE_BUILD_SHIPPING

						OnNewItemHovered.Broadcast(HitInteractableInterface);
					}
				}
				else if(HoveredInteractable.GetObject() != nullptr)
				{
					ResetHoveredInteractable();
				}
			}
		}
	}
	else
	{
		ResetHoveredInteractable();
	}

	SetLastKnownTransform();
	IsAlreadyProcessingLook = false;
}

void UInteractionComponent::ResetHoveredInteractable()
{
	if (HoveredInteractable)
	{
#if !UE_BUILD_SHIPPING
		UE_LOG(InteractionComponentLog, Log, TEXT("No longer looking at %s, clearing"), *HoveredInteractable.GetObject()->GetName());
#endif //!UE_BUILD_SHIPPING

		HoveredInteractable.SetObject(nullptr);
		HoveredInteractable.SetInterface(nullptr);
		OnNewItemHovered.Broadcast(nullptr);
	}
}

void UInteractionComponent::StartInteraction()
{
	if (HoveredInteractable)
	{
#if !UE_BUILD_SHIPPING
		UE_LOG(InteractionComponentLog, Log, TEXT("Starting interaction"));
#endif //!UE_BUILD_SHIPPING
		HoveredInteractable->OnInteract(CachedOwningPawn);
	}
}

void UInteractionComponent::EndInteraction()
{
	if (HoveredInteractable)
	{
#if !UE_BUILD_SHIPPING
		UE_LOG(InteractionComponentLog, Log, TEXT("Ending interaction"));
#endif //!UE_BUILD_SHIPPING

		//EndInteraction
	}
}
