// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/HealthComponent.h"
#include "InteractionComponent.h"
#include "AirMovementComponent.h"
#include "AirInventory.h"

#include "AirChar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharLanded);

UCLASS()
class AIRSHIP_API AAirChar : public ACharacter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = Inventory)
	UAirInventory* GetInventory() { return InventoryComponent; }
public:
	// Sets default values for this character's properties
	AAirChar();

	UHealthComponent* HealthComponent;
	UInteractionComponent* InteractionComponent;
	UAirMovementComponent* MovementComponent;
	UAirInventory* InventoryComponent;

	FOnCharLanded OnCharLanded;

	virtual void Landed(const FHitResult& Hit) override;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region MovementParams



#pragma endregion MovementParams

	

	
	
};
