// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "AirInventory.h"
#include "TransferWindowBase.h"
#include "Container.generated.h"

//////////////////////////////////////////////////////////////////////////
// Base class for all containers, so barrels, chests, lockboxes, etc.
//////////////////////////////////////////////////////////////////////////

UCLASS()
class AIRSHIP_API AContainer : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AContainer();	

	UPROPERTY(EditDefaultsOnly, Category = UI)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	UAirInventory* Inventory;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UTransferWindowBase> TransferWidget;

public:

	/************************************************************************/
	/* Interaction Interface                                                */
	/************************************************************************/

	virtual void OnInteract(AActor* InteractingActor) override;
};
