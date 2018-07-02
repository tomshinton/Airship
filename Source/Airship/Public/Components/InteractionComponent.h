// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIRSHIP_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void StartInteraction();
	void EndInteraction();

private:
	UFUNCTION()
	void UpdateHoveredActor(AActor* NewHoveredActor);
	AActor* HoveredActor;
};
