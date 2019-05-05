// Fill out your copyright notice in the Description page of Project Settings.

#include "AirController.h"
#include "AirChar.h"
#include "Utils/Defs/CollisionDefs.h"

DECLARE_CYCLE_STAT(TEXT("ControllerLookAt"), STAT_LookAt, STATGROUP_ControllerFunctions);

AAirController::AAirController()
	: LookAtDistance(10000.f)
	, LookAtFrequency(1/15.f)
{

}

void AAirController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(LookAtTimerHandle, this, &AAirController::LookAt, LookAtFrequency, true, 0.f);
	}
}

void AAirController::LookAt()
{
	SCOPE_CYCLE_COUNTER(STAT_LookAt)
	FHitResult HitRes;

	if (TraceSceneChanged())
	{
		if (UWorld* World = GetWorld())
		{
			FCollisionQueryParams TraceParams;
			const FName TraceTag = "LookAt";

			const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());          
			const FVector2D  ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);

			TraceParams.AddIgnoredActor(GetPawn());
			TraceParams.bTraceComplex = false;
			TraceParams.TraceTag = TraceTag;

			FVector StartLocation;
			FVector TraceDirection;

			DeprojectScreenPositionToWorld(ViewportCenter.X, ViewportCenter.Y, StartLocation, TraceDirection);

			const FVector EndLocation = StartLocation + (TraceDirection * 10000.f);

			World->LineTraceSingleByChannel(HitRes, StartLocation, EndLocation, CC_LOOKANDUSE, TraceParams);
			
			if (HitRes.bBlockingHit)
			{
				CurrentLookAtActor = HitRes.Actor.Get();
				CachedObjectTransform = CurrentLookAtActor->GetActorTransform();
			}

			CachedPawnTransform = GetPawn()->GetActorTransform();

			if (CurrentLookAtActor != LastLookAtActor)
			{
				if (OnLookAtChanged.IsBound())
				{
					OnLookAtChanged.Broadcast(CurrentLookAtActor);
				}
			}

			LastLookAtActor = CurrentLookAtActor;
		}
	}
}

bool AAirController::TraceSceneChanged()
{
	if (!CurrentLookAtActor)
	{
		return true;
	} 
	else if (CurrentLookAtActor->GetActorTransform().GetLocation() != CachedObjectTransform.GetLocation() || CurrentLookAtActor->GetActorTransform().GetRotation() != CachedObjectTransform.GetRotation())
	{
		return true;
	}

	return true;
}
