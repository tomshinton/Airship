// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/UI/Public/AirWidget.h"
#include "AirChar.h"
#include "Engine/Engine.h"

UAirWidget::UAirWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, LocalChar(nullptr)
{}

void UAirWidget::Build()
{
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
}

void UAirWidget::OnBuild_Implementation(){}
