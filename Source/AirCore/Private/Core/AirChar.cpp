// Fill out your copyright notice in the Description page of Project Settings.

#include "AirChar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ConstructorHelpers.h"
#include <DrawDebugHelpers.h>
#include "AirHUD.h"
#include "AirController.h"
#include "AirMovementComponent.h"
#include "InteractionComponent.h"
#include "HealthComponent.h"
#include "AirInventory.h"

// Sets default values
AAirChar::AAirChar()
	: LeftHandTargetLocation(FVector(40.f, 30.f, 40.f))
	, RightHandTargetTransform(FVector(40.f, -30.f, 40.f))
	, HandBlendTime(1.f)
	, Camera(CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")))
	, RightHand(CreateDefaultSubobject<USceneComponent>(TEXT("RightHandComponent")))
	, MovementComponent(CreateDefaultSubobject<UAirMovementComponent>(TEXT("MovementComponent")))
	, HealthComponent(CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent")))
	, InteractionComponent(CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent")))
	, InventoryComponent(CreateDefaultSubobject<UAirInventory>(TEXT("InventoryComponent")))
{
	PrimaryActorTick.bCanEverTick = true;

	Camera->SetupAttachment(RootComponent);

	RightHand->SetupAttachment(Camera);
	RightHand->SetRelativeLocation(FVector(RightHandTargetTransform.GetLocation()));

	MovementComponent->SetCameraComponent(Camera);
	InventoryComponent->InventorySize = 20;
	InventoryComponent->HotbarSlots = 10;
	InventoryComponent->SetHandComponents(LeftHand, RightHand);

	bUseControllerRotationYaw = false;
}

void AAirChar::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FTransform NewRightHandTransform = RightHandTargetTransform;

	if (InventoryComponent->GetIsAiming())
	{
		FVector NewLocation = NewRightHandTransform.GetLocation();
		NewLocation.Y = 0;

		NewRightHandTransform.SetLocation(NewLocation);
	}
	else if (ShouldLowerHands())
	{
		FVector NewLocation = NewRightHandTransform.GetLocation();
		NewLocation.Z -= HandOffset;
		
		NewRightHandTransform.SetLocation(NewLocation);
	}

	RightHand->SetRelativeLocation(FMath::VInterpTo(RightHand->RelativeLocation, NewRightHandTransform.GetLocation(), DeltaSeconds, HandBlendTime));
}

void AAirChar::BeginPlay()
{
	Super::BeginPlay();
	RightHandTargetTransform = RightHand->GetRelativeTransform();

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

	PlayerInputComponent->BindAction("StartPrimary", IE_Pressed, InventoryComponent, &UAirInventory::StartPrimary);
	PlayerInputComponent->BindAction("EndPrimary", IE_Released, InventoryComponent, &UAirInventory::EndPrimary);
	PlayerInputComponent->BindAction("StartSecondary", IE_Pressed, InventoryComponent, &UAirInventory::StartSecondary);
	PlayerInputComponent->BindAction("EndSecondary", IE_Released, InventoryComponent, &UAirInventory::EndSecondary);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, InventoryComponent, &UAirInventory::Reload);
}

bool AAirChar::ShouldLowerHands()
{
	if (MovementComponent->GetIsSprinting() || GetCharacterMovement()->IsFalling())
	{
		return true;
	}

	return false;
}





