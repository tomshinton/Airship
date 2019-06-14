// Fill out your copyright notice in the Description page of Project Settings.

#include "AirController.h"
#include "InteractionComponent.h"

namespace
{
	namespace AirControllerPrivate
	{
		const FName InteractionComponentName = TEXT("InteractionComponent");
	}
}

AAirController::AAirController()
	: InteractionComponent(CreateDefaultSubobject<UInteractionComponent>(AirControllerPrivate::InteractionComponentName))
{}
