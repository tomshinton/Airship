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

void UInteractionComponent::GetLookAtLocations(const FVector2D& InViewportCentre, FVector& TraceStart, FVector& TraceEnd) const
{
	if (APlayerController* OwningController = Cast<APlayerController>(GetOwner()))
	{
		FVector TraceDirection = FVector(ForceInitToZero);

		OwningController->DeprojectScreenPositionToWorld(InViewportCentre.X, InViewportCentre.Y, TraceStart, TraceDirection);
		TraceEnd = TraceStart + (TraceDirection * LookAtDistance);
	}
}

bool UInteractionComponent::ShouldTrace() const
{
	return FMath::IsNearlyZero(CurrentTraceCooldown) || !GetCurrentOwnerTransform().Equals(LastKnownOwnerTransform);
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
	if (CachedWorld && !IsAlreadyProcessingLook)
	{
		if(ShouldTrace())
		{ 
			CurrentTraceCooldown = FlatRefreshTime;

			if (GEngine)
			{
				FVector2D ViewportSize = FVector2D::ZeroVector;
				ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

				const FVector2D ViewportCenter = ViewportSize * 0.5f;

				FVector TraceStart = FVector::ZeroVector;
				FVector TraceEnd = FVector::ZeroVector;

				GetLookAtLocations(ViewportCenter, TraceStart, TraceEnd);

				CachedWorld->AsyncLineTraceByChannel(EAsyncTraceType::Single, TraceStart, TraceEnd, CC_LOOKANDUSE, CachedTraceParams, FCollisionResponseParams(), &OnLookOverDelegate);
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
			DrawDebugPoint(CachedWorld, InHits[0].Location, 20.f, FColor::Green);
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