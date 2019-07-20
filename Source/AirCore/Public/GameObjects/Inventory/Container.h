// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AirInventory.h"
#include "TransferWindowBase.h"
#include "InteractableInterface.h"
#include "Container.generated.h"

//////////////////////////////////////////////////////////////////////////
// Base class for all containers, so barrels, chests, lockboxes, etc.
//////////////////////////////////////////////////////////////////////////

UCLASS()
class AContainer : public AActor,
	public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AContainer();	

	UPROPERTY(EditDefaultsOnly, Category = UI)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	UAirInventory* Inventory;

	//InteractableInterface
	virtual void OnInteract(AActor* InteractingActor) override;
	virtual FText GetDisplayName() const override { return FText::FromString(TEXT("Container")); };
	//~InteractableInterface
};
