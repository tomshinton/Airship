// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "AirMovementComponent.generated.h"

class AAirChar;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AIRSHIP_API UAirMovementComponent : public UActorComponent
{
	GENERATED_BODY()

	UAirMovementComponent();

public:
	void MoveForward(float InAxis);
	void MoveRight(float InAxis);
	void LookRight(float InAxis);
	void LookUp(float InAxis);

	void StartJump();
	void EndJump();

	float GetModifiedMoveSpeed(const float InVal);
	void GetModifiedSprintFromCurve(float& InVal);

	void ToggleSprint();

private:
	float MaxCameraPitch;
	float TurnSpeed;
	float TiltCameraSpeed;
	float StrafeSpeed;

	float LastTurnValue;
	float MaxTurnValue;

	float ForwardSpeed;
	float BackwardsSpeed;

	bool IsSprinting;
	float SprintModifier;

	UCurveFloat * BankingCurve;

private:
	AAirChar * OwningCharacter;
};
