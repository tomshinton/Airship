// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/Engine/Classes/Components/ActorComponent.h>

#include "AirMovementComponent.generated.h"

class AAirChar;
class UCharacterMovementComponent;
class UCameraComponent;
class UCameraShake;
class UCurveFloat;

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

	float GetModifiedMoveSpeed(const float InVal);
	void GetModifiedSprintFromCurve(float& InVal);
	bool GetIsSprinting() const { return IsSprinting; }

	void ToggleSprint();
	void ApplyCameraShakes();
	TSubclassOf<UCameraShake> GetAppropriateCameraShake();

	virtual void BeginPlay() override;
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
	UCharacterMovementComponent* OwningMovementComponent;
	
	UPROPERTY()
	UCameraComponent* OwnerCamera;
};
