// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include <Camera/CameraComponent.h>
#include "AirMovementComponent.generated.h"

class AAirChar;

UCLASS()
class UAirMovementComponent : public UActorComponent
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

	void SetCameraComponent(UCameraComponent* InCameraComponent) { OwnerCamera = InCameraComponent; }

	float GetModifiedMoveSpeed(const float InVal);
	void GetModifiedSprintFromCurve(float& InVal);
	bool GetIsSprinting() const { return IsSprinting; }

	void ToggleSprint();
	void ApplyCameraShakes();
	TSubclassOf<UCameraShake> GetAppropriateCameraShake();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

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

	UPROPERTY()
	UCurveFloat* BankingCurve;

	UPROPERTY()
	AAirChar* OwningCharacter;

	UPROPERTY()
	UCameraComponent* OwnerCamera;
};
