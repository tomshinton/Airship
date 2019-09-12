// Airship Project - Tom Shinton 2018

#pragma once

#include "Camera/CameraShake.h"
#include "CameraBobs.generated.h"

UCLASS()
class UWalkBob : public UCameraShake
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

		LocOscillation.Z.Amplitude = .1f;
		LocOscillation.Z.Frequency = 6.f;
		LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	}
};

UCLASS()
class URunBob : public UCameraShake
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

		LocOscillation.Z.Amplitude = .1f;
		LocOscillation.Z.Frequency = 12.f;
		LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	}
};
