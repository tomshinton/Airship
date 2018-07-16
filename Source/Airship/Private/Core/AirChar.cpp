// Fill out your copyright notice in the Description page of Project Settings.

#include "AirChar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ConstructorHelpers.h"
#include <DrawDebugHelpers.h>

// Sets default values
AAirChar::AAirChar()
	: LeftHandTargetLocation(FVector(40.f, 30.f, 40.f))
	, RightHandTargetLocation(FVector(40.f, -30.f, 40.f))
{
	PrimaryActorTick.bCanEverTick = true;

	RightHand = CreateDefaultSubobject<USceneComponent>(TEXT("RightHandComponent"));
	RightHand->SetupAttachment(RootComponent);
	RightHand->SetRelativeLocation(FVector(RightHandTargetLocation));

	LeftHand = CreateDefaultSubobject<USceneComponent>(TEXT("LeftHandComponent"));
	LeftHand->SetupAttachment(RootComponent);
	RightHand->SetRelativeLocation(LeftHandTargetLocation);

	MovementComponent = CreateDefaultSubobject<UAirMovementComponent>(TEXT("MovementComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	InventoryComponent = CreateDefaultSubobject<UAirInventory>(TEXT("InventoryComponent"));
	InventoryComponent->InventorySize = 20;
	InventoryComponent->SetHandComponents(LeftHand, RightHand);
}

void AAirChar::Landed(const FHitResult& Hit)
{
	OnCharLanded.Broadcast();
}

void AAirChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", MovementComponent, &UAirMovementComponent::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", MovementComponent, &UAirMovementComponent::MoveRight);
	PlayerInputComponent->BindAxis("LookRight", MovementComponent, &UAirMovementComponent::LookRight);
	PlayerInputComponent->BindAxis("LookUp", MovementComponent, &UAirMovementComponent::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, MovementComponent, &UAirMovementComponent::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, MovementComponent, &UAirMovementComponent::EndJump);

	//Act as a flip-flop
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, MovementComponent, &UAirMovementComponent::ToggleSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, MovementComponent, &UAirMovementComponent::ToggleSprint);

	PlayerInputComponent->BindAction("Use", IE_Pressed, InteractionComponent, &UInteractionComponent::StartInteraction);
	PlayerInputComponent->BindAction("Use", IE_Released, InteractionComponent, &UInteractionComponent::EndInteraction);

	PlayerInputComponent->BindAction("FocusNextItem", IE_Pressed, InventoryComponent, &UAirInventory::FocusNextItem);
	PlayerInputComponent->BindAction("FocusLastItem", IE_Pressed, InventoryComponent, &UAirInventory::FocusLastItem);
}











