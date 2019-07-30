// Airship Project - Tom Shinton 2018

#include "Runtime/UI/Public/AirWidget.h"

#include <AirCore/Public/Core/AirChar.h>

UAirWidget::UAirWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, LocalChar(nullptr)
	, NativeConstructCalled(false)
{}

void UAirWidget::Build()
{
	checkf(NativeConstructCalled, TEXT("Cannot call build on a non-initialised AirWidget - did you forget the Super on nativeConstruct?"));
	OnBuild();
}

void UAirWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (UWorld* World = GetWorld())
	{
		if (APlayerController* FirstPlayerController = World->GetFirstPlayerController())
		{
			if (AAirChar* FirstCharFound = Cast<AAirChar>(FirstPlayerController->GetPawn()))
			{
				LocalChar = FirstCharFound;
			}
		}
	}

	NativeConstructCalled = true;
}

void UAirWidget::OnBuild_Implementation(){}
