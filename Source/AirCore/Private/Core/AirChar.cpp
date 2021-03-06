// Airship Project - Tom Shinton 2018

#include "AirCore/Public/Core/AirChar.h"
#include "AirCore/Public/Core/AirController.h"
#include "AirCore/Public/Core/AirHUD.h"
#include "AirCore/Public/Components/Gameplay/AirMovementComponent.h"
#include "AirCore/Public/Components/Gameplay/HealthComponent.h"
#include "AirCore/Public/Components/Gameplay/InteractionComponent.h"

#include <Runtime/Engine/Classes/Camera/CameraComponent.h>
#include <Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h>
#include <Runtime/Input/Public/AirInputComponent.h>
#include <Runtime/Inventory/Public/InventoryComponent/AirInventory.h>

AAirChar::AAirChar()
	: Camera(CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")))
	, RightHand(CreateDefaultSubobject<USceneComponent>(TEXT("RightHandComponent")))
	, HandBlendTime(1.f)
	, HealthComponent(CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent")))
	, MovementComponent(CreateDefaultSubobject<UAirMovementComponent>(TEXT("MovementComponent")))
	, InventoryComponent(CreateDefaultSubobject<UAirInventory>(TEXT("InventoryComponent")))
	, RightHandTargetTransform(FVector(40.f, -30.f, 40.f))
	, LeftHandTargetLocation(FVector(40.f, 30.f, 40.f))
	, CachedInputComponent(nullptr)
{
	InputComponentClass = UAirInputComponent::StaticClass();

	PrimaryActorTick.bCanEverTick = true;

	Camera->SetupAttachment(RootComponent);

	RightHand->SetupAttachment(Camera);
	RightHand->SetRelativeLocation(FVector(RightHandTargetTransform.GetLocation()));

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
	RightHandTargetTransform = RightHand->GetRelativeTransform();

	if (UWorld* World = GetWorld())
	{
		CachedWorld = World;
	}

	Super::BeginPlay();
}

void AAirChar::Landed(const FHitResult& Hit)
{
	OnCharLanded.Broadcast();
}

void AAirChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	CachedInputComponent = PlayerInputComponent;

	PlayerInputComponent->BindAxis("MoveForward", MovementComponent, &UAirMovementComponent::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", MovementComponent, &UAirMovementComponent::MoveRight);
	PlayerInputComponent->BindAxis("LookRight", MovementComponent, &UAirMovementComponent::LookRight);
	PlayerInputComponent->BindAxis("LookUp", MovementComponent, &UAirMovementComponent::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, MovementComponent, &UAirMovementComponent::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, MovementComponent, &UAirMovementComponent::EndJump);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, MovementComponent, &UAirMovementComponent::ToggleSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, MovementComponent, &UAirMovementComponent::ToggleSprint);

	PlayerInputComponent->BindAction("FocusNextItem", IE_Pressed, InventoryComponent, &UAirInventory::FocusNextItem);
	PlayerInputComponent->BindAction("FocusLastItem", IE_Pressed, InventoryComponent, &UAirInventory::FocusLastItem);

	PlayerInputComponent->BindAction("StartPrimary", IE_Pressed, InventoryComponent, &UAirInventory::StartPrimary);
	PlayerInputComponent->BindAction("EndPrimary", IE_Released, InventoryComponent, &UAirInventory::EndPrimary);
	PlayerInputComponent->BindAction("StartSecondary", IE_Pressed, InventoryComponent, &UAirInventory::StartSecondary);
	PlayerInputComponent->BindAction("EndSecondary", IE_Released, InventoryComponent, &UAirInventory::EndSecondary);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, InventoryComponent, &UAirInventory::Reload);

	DeferUIBinding(PlayerInputComponent);
}

void AAirChar::DeferUIBinding(UInputComponent* PlayerInputComponent)
{
	if (AAirController* AirController = Cast<AAirController>(GetController()))
	{
		if (AAirHUD* AirHUD = Cast<AAirHUD>(AirController->GetHUD()))
		{
			AirHUD->CachePlayerInputComponent(PlayerInputComponent);
		}
	}
}

bool AAirChar::ShouldLowerHands()
{
	if (MovementComponent->GetIsSprinting() || GetCharacterMovement()->IsFalling())
	{
		return true;
	}

	return false;
}






