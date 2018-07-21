// Fill out your copyright notice in the Description page of Project Settings.

#include "AirChar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ConstructorHelpers.h"
#include <DrawDebugHelpers.h>
#include "AirHUD.h"
#include "AirController.h"

// Sets default values
AAirChar::AAirChar()
	: LeftHandTargetLocation(FVector(40.f, 30.f, 40.f))
	, RightHandTargetLocation(FVector(40.f, -30.f, 40.f))
	, HandBlendTime(1.f)
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	RightHand = CreateDefaultSubobject<USceneComponent>(TEXT("RightHandComponent"));
	RightHand->SetupAttachment(Camera);
	RightHand->SetRelativeLocation(FVector(RightHandTargetLocation));

	LeftHand = CreateDefaultSubobject<USceneComponent>(TEXT("LeftHandComponent"));
	LeftHand->SetupAttachment(Camera);
	RightHand->SetRelativeLocation(LeftHandTargetLocation);

	MovementComponent = CreateDefaultSubobject<UAirMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->SetCameraComponent(Camera);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	InventoryComponent = CreateDefaultSubobject<UAirInventory>(TEXT("InventoryComponent"));
	InventoryComponent->InventorySize = 20;
	InventoryComponent->SetHandComponents(LeftHand, RightHand);
}

void AAirChar::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector NewRightHandLoc = RightHandTargetLocation;
	FVector NewLeftHandLoc = LeftHandTargetLocation;

	if (ShouldLowerHands())
	{
		NewRightHandLoc.Z -= HandOffset;
		NewLeftHandLoc.Z -= HandOffset;
	}

	RightHand->SetRelativeLocation(FMath::VInterpTo(RightHand->RelativeLocation, NewRightHandLoc, DeltaSeconds, HandBlendTime));
	LeftHand->SetRelativeLocation(FMath::VInterpTo(LeftHand->RelativeLocation, NewLeftHandLoc, DeltaSeconds, HandBlendTime));
}

void AAirChar::BeginPlay()
{
	Super::BeginPlay();

	LeftHandTargetLocation = LeftHand->RelativeLocation;
	RightHandTargetLocation = RightHand->RelativeLocation;
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

	if (AAirController* OwningController = Cast<AAirController>(GetController()))
	{
		if (AAirHUD* SpawnedHUD = Cast<AAirHUD>(OwningController->GetHUD()))
		{
			PlayerInputComponent->BindAction("ToggleInventory", IE_Pressed, SpawnedHUD, &AAirHUD::ToggleInventoryScreen);
		}
	}

	PlayerInputComponent->BindAction("StartPrimary", IE_Pressed, InventoryComponent, &UAirInventory::StartPrimary);
	PlayerInputComponent->BindAction("EndPrimary", IE_Released, InventoryComponent, &UAirInventory::EndPrimary);
	PlayerInputComponent->BindAction("StartSecondary", IE_Pressed, InventoryComponent, &UAirInventory::StartSecondary);
	PlayerInputComponent->BindAction("EndSecondary", IE_Released, InventoryComponent, &UAirInventory::EndSecondary);
}

bool AAirChar::ShouldLowerHands()
{
	if (MovementComponent->GetIsSprinting() || GetCharacterMovement()->IsFalling())
	{
		return true;
	}

	return false;
}










