// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "AirPawn.generated.h"

UCLASS()
class AAirPawn : public APawn
{
	GENERATED_BODY()

public:
	AAirPawn();

	UCapsuleComponent* PlayerCapsule;
	UCameraComponent* CamComponent;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float InAxis);
	void MoveRight(float InAxis);
	void LookRight(float InAxis);
	void LookUp(float InAxis);
	
	void Jump();

	float MaxCameraPitch;
	float TurnSpeed;
	float TiltCameraSpeed;
	float StrafeSpeed;
	float ForwardSpeed;
	float BackwardsSpeed;
};
