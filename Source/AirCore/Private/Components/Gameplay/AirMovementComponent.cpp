// Airship Project - Tom Shinton 2018

#include "AirCore/Public/Components/Gameplay/AirMovementComponent.h"

#include "AirCore/Public/Core/AirChar.h"
#include "AirCore/Public/Core/AirController.h"
#include "AirCore/Public/Shakes/CameraBobs.h"

#include <Runtime/Engine/Classes/Camera/CameraComponent.h>
#include <Runtime/Engine/Classes/Camera/CameraShake.h>
#include <Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h>
#include <Runtime/UI/Public/Utils/HUDTools.h>

UAirMovementComponent::UAirMovementComponent()
	: MaxCameraPitch(40.f)
	, TurnSpeed(1.f)
	, TiltCameraSpeed(.5f)
	, StrafeSpeed(350.f)
	, LastTurnValue(0.f)
	, MaxTurnValue(3.f)
	, ForwardSpeed(400.f)
	, BackwardsSpeed(200.f)
	, IsSprinting(false)
	, SprintModifier(1.5f)
	, BankingCurve(nullptr)
	, OwningCharacter(nullptr)
	, OwningMovementComponent(nullptr)
	, OwnerCamera(nullptr)
{
	static ConstructorHelpers::FObjectFinder<UCurveFloat> BankingCurveRef(TEXT("CurveFloat'/Game/Data/Curves/C_Player_Banking.C_Player_Banking'"));
	if (BankingCurveRef.Object)
	{
		BankingCurve = BankingCurveRef.Object;
	}

	PrimaryComponentTick.bCanEverTick = true;
}

void UAirMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningCharacter = Cast<AAirChar>(GetOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent = Cast<UCharacterMovementComponent>(OwningCharacter->GetMovementComponent());
		OwnerCamera = OwningCharacter->FindComponentByClass<UCameraComponent>();
	}
}

void UAirMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	ApplyCameraShakes();
}

void UAirMovementComponent::MoveForward(float InAxis)
{
	if (!FMath::IsNearlyZero(InAxis))
	{
		OwningMovementComponent->MaxWalkSpeed = GetModifiedMoveSpeed(InAxis);
		OwningCharacter->AddMovementInput(OwningCharacter->GetActorForwardVector(), InAxis);
	}
}

void UAirMovementComponent::MoveRight(float InAxis)
{
	if (!FMath::IsNearlyZero(InAxis))
	{
		OwningMovementComponent->MaxWalkSpeed = StrafeSpeed;
		OwningCharacter->AddMovementInput(OwningCharacter->GetActorRightVector(), InAxis);
	}
}

void UAirMovementComponent::LookRight(float InAxis)
{
	LastTurnValue = InAxis;

	if (!UHUDTools::IsMouseVisible(*OwningCharacter))
	{
		if (OwnerCamera && OwningCharacter)
		{
			const FRotator CurrentRotation = OwningCharacter->GetActorRotation();
			const FRotator TargetRotation = CurrentRotation + FRotator(0.f, InAxis*TurnSpeed, 0.f);

			OwningCharacter->SetActorRotation(TargetRotation);
		}
	}
}

void UAirMovementComponent::LookUp(float InAxis)
{
	if (!UHUDTools::IsMouseVisible(*OwningCharacter))
	{
		if (OwnerCamera)
		{
			const float NewPitch = FMath::Clamp(OwnerCamera->RelativeRotation.Pitch + (-InAxis * TiltCameraSpeed), -MaxCameraPitch, MaxCameraPitch);
			FRotator NewRotation = OwnerCamera->RelativeRotation;
			NewRotation.Pitch = NewPitch;
			OwnerCamera->SetRelativeRotation(NewRotation);
		}
	}
}

void UAirMovementComponent::StartJump()
{
 	OwningCharacter->bPressedJump = true;
}

void UAirMovementComponent::EndJump()
{
	OwningCharacter->bPressedJump = false;
}

float UAirMovementComponent::GetModifiedMoveSpeed(const float InVal)
{
	if (!FMath::IsNearlyZero(InVal))
	{
		const float LinearVal = InVal > 0 ? ForwardSpeed : BackwardsSpeed;
		float ModifiedVal = LinearVal * (IsSprinting ? SprintModifier : 1.f);
		GetModifiedSprintFromCurve(ModifiedVal);
		return ModifiedVal;
	}

	return 0.f;
}

void UAirMovementComponent::GetModifiedSprintFromCurve(float& InVal)
{
	if (BankingCurve && !FMath::IsNearlyZero(MaxTurnValue))
	{
		const float NormalisedVal = FMath::Clamp(LastTurnValue / MaxTurnValue, 0.f, 1.f);
		InVal *= BankingCurve->GetFloatValue(NormalisedVal);
	}
}

void UAirMovementComponent::ToggleSprint()
{
	IsSprinting = !IsSprinting;
}

void UAirMovementComponent::ApplyCameraShakes()
{
	if(AAirController* OwningController = Cast<AAirController>(OwningCharacter->GetController()))
	{
		OwningController->ClientPlayCameraShake(GetAppropriateCameraShake(), 1.f, ECameraAnimPlaySpace::CameraLocal);
	}
}

TSubclassOf<UCameraShake> UAirMovementComponent::GetAppropriateCameraShake()
{
	if (GetOwner()->GetVelocity().Size() > 0.f)
	{
		if (IsSprinting)
		{
			return URunBob::StaticClass();
		}
		else
		{
			return UWalkBob::StaticClass();
		}
	}

	return UCameraShake::StaticClass();
}
