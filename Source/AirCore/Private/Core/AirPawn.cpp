// Fill out your copyright notice in the Description page of Project Settings.

#include "AirPawn.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAirPawn::AAirPawn()
	: MaxCameraPitch(20.f)
	, TurnSpeed(1.f)
	, TiltCameraSpeed(.5f)
	, StrafeSpeed(1.f)
	, ForwardSpeed(2.f)
	, BackwardsSpeed(.5f)
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerCapsule"));
	RootComponent = PlayerCapsule;
	PlayerCapsule->SetCapsuleHalfHeight(90.f, true);
	PlayerCapsule->SetCapsuleRadius(35.f);
	PlayerCapsule->SetCollisionProfileName("BlockAll");

	CamComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CamComponent->SetupAttachment(RootComponent);
	CamComponent->SetRelativeLocation(FVector(0, 0, PlayerCapsule->GetScaledCapsuleHalfHeight() - 10));

}

void AAirPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAirPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAirPawn::MoveRight);
	PlayerInputComponent->BindAxis("LookRight", this, &AAirPawn::LookRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AAirPawn::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AAirPawn::Jump);
}

void AAirPawn::MoveForward(float InAxis)
{
	const float MoveSpeed = InAxis > 0.f ? ForwardSpeed : BackwardsSpeed;
	const FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * (InAxis * MoveSpeed));
	SetActorLocation(NewLocation, true);

}

void AAirPawn::MoveRight(float InAxis)
{
	const FVector NewLocation = GetActorLocation() + (GetActorRightVector() * (InAxis * StrafeSpeed));
	SetActorLocation(NewLocation, true);
}

void AAirPawn::LookRight(float InAxis)
{
	const FRotator NewRotation = GetActorRotation() + FRotator(0.f, InAxis * TurnSpeed, 0.f);
	SetActorRotation(NewRotation);
}

void AAirPawn::LookUp(float InAxis)
{
	FRotator CachedRotation = CamComponent->GetComponentRotation();
	const float ClampedPitch = FMath::Clamp(CachedRotation.Pitch + (InAxis * TiltCameraSpeed), -MaxCameraPitch, MaxCameraPitch);
	CachedRotation.Pitch = ClampedPitch;
	CamComponent->SetWorldRotation(CachedRotation);
}

void AAirPawn::Jump()
{

}

