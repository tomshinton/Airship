// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShake.h"
#include "CameraBobs.generated.h"

UCLASS()
class AIRSHIP_API UWalkBob : public UCameraShake
{
	GENERATED_BODY()

	UWalkBob()
	{
		OscillationDuration = 1.f;
		OscillationBlendInTime = .1f;
		OscillationBlendOutTime = .2f;

		RotOscillation.Pitch.Amplitude = .05f;
		RotOscillation.Pitch.Frequency = 12.f;
		RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
/*
		RotOscillation.Yaw.Amplitude = .05f;
		RotOscillation.Yaw.Frequency = 6.f;
		RotOscillation.Yaw.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;

		RotOscillation.Roll.Amplitude = .05f;
		RotOscillation.Roll.Frequency = 3.5f;
		RotOscillation.Roll.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
*/
		LocOscillation.Z.Amplitude = .1f;
		LocOscillation.Z.Frequency = 6.f;
		LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	}
};

UCLASS()
class AIRSHIP_API URunBob : public UCameraShake
{
	GENERATED_BODY()

	URunBob()
	{
		OscillationDuration = 1.f;
		OscillationBlendInTime = .1f;
		OscillationBlendOutTime = .2f;

		RotOscillation.Pitch.Amplitude = .05f;
		RotOscillation.Pitch.Frequency = 12.f;
		RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
/*
		RotOscillation.Yaw.Amplitude = .05f;
		RotOscillation.Yaw.Frequency = 6.f;
		RotOscillation.Yaw.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;

		RotOscillation.Roll.Amplitude = .05f;
		RotOscillation.Roll.Frequency = 3.5f;
		RotOscillation.Roll.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
*/
		LocOscillation.Z.Amplitude = .1f;
		LocOscillation.Z.Frequency = 12.f;
		LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	}
};