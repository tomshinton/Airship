// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponent.h"
#include "AirChar.h"
#include "AirController.h"
#include "InteractionInterface.h"

void UInteractionComponent::BeginPlay()
{
	if (AAirChar* OwningChar = Cast<AAirChar>(GetOwner()))
	{
		if (AAirController* OwningController = Cast<AAirController>(OwningChar->GetController()))
		{
			OwningController->OnLookAtChanged.AddDynamic(this, &UInteractionComponent::UpdateHoveredActor);
		}
	}
}

void UInteractionComponent::StartInteraction()
{
	if (HoveredActor)
	{
		if (HoveredActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			IInteractionInterface::Execute_OnInteract(HoveredActor);
		}
	}
}

void UInteractionComponent::EndInteraction()
{

}

void UInteractionComponent::UpdateHoveredActor(AActor* NewHoveredActor)
{
	HoveredActor = NewHoveredActor;
}

