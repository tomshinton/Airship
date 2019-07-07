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

DEFINE_LOG_CATEGORY_STATIC(InteractionComponent, Log, Log);

UInteractionComponent::UInteractionComponent()
	: HoveredActor(nullptr)
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

void UInteractionComponent::SetupInput(APawn* InNewPawn)
{
	if (AAirChar* OwningPawn = Cast<AAirChar>(InNewPawn))
	{
		CachedOwningPawn = OwningPawn;

		if (UInputComponent* CachedInputComponent = CachedOwningPawn->GetCachedInputComponent())
		{

			UE_LOG(InteractionComponent, Log, TEXT("Setting up Interaction bindings"));

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
		if(ShouldTrace())
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
	else
	{
		UE_LOG(InteractionComponent, Log, TEXT("Attempting trace whilst Trace is blocked - bailing"));
	}
}

void UInteractionComponent::OnLookOver(const TArray<FHitResult>& InHits)
{
	if (InHits.Num() > 0)
	{
		if (AActor* FirstHit = InHits[0].Actor.Get())
		{
			UE_LOG(InteractionComponent, Log, TEXT("OnLookAtOver: Looking at %s"), *FirstHit->GetName());
			
			HoveredActor = FirstHit;
		}
	}

	SetLastKnownTransform();
	IsAlreadyProcessingLook = false;
}

void UInteractionComponent::StartInteraction()
{
	UE_LOG(InteractionComponent, Log, TEXT("Starting interaction"));

	if (HoveredActor)
	{
		if (IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(HoveredActor))
		{
			InteractionInterface->OnInteract(CachedOwningPawn);
		}
	}
}

void UInteractionComponent::EndInteraction()
{
	UE_LOG(InteractionComponent, Log, TEXT("Ending interaction"));

}