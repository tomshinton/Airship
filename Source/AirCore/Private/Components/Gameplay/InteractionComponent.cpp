// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponent.h"
#include "AirChar.h"
#include "AirController.h"
#include "InteractionInterface.h"
#include "GameFramework/Controller.h"
#include "Engine/Engine.h"
#include "Utils/Defs/CollisionDefs.h"
#include <CollisionQueryParams.h>
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "Utils/Functions/InterfaceHelpers.h"
#include "InteractableInterface.h"

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

			CachedInputComponent->BindAction("Use", IE_Pressed, this, &UInteractionComponent::StartInteraction);
			CachedInputComponent->BindAction("Use", IE_Released, this, &UInteractionComponent::EndInteraction);
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

						UE_LOG(InteractionComponentLog, Log, TEXT("Caching %s for interactions"), *FirstHit->GetName());

						OnNewItemHovered.Broadcast(HitInteractableInterface);
					}
				}
				else if(HoveredInteractable.GetObject() != nullptr)
				{
					UE_LOG(InteractionComponentLog, Log, TEXT("No longer looking at %s, clearing"), *HoveredInteractable.GetObject()->GetName());

					HoveredInteractable.SetObject(nullptr);
					HoveredInteractable.SetInterface(nullptr);
					OnNewItemHovered.Broadcast(nullptr);
				}
			}
		}
	}

	SetLastKnownTransform();
	IsAlreadyProcessingLook = false;
}

void UInteractionComponent::StartInteraction()
{
	if (HoveredInteractable)
	{
		UE_LOG(InteractionComponentLog, Log, TEXT("Starting interaction"));
		HoveredInteractable->OnInteract(CachedOwningPawn);
	}
}

void UInteractionComponent::EndInteraction()
{
	if (HoveredInteractable)
	{
		UE_LOG(InteractionComponentLog, Log, TEXT("Ending interaction"));
		//EndInteraction
	}
}