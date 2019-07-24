// Fill out your copyright notice in the Description page of Project Settings.

#include "AirWidget.h"
#include "AirChar.h"
#include <WidgetAnimation.h>
#include <MovieScene.h>
#include "Engine/Engine.h"

UAirWidget::UAirWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, LocalChar(nullptr)
	, AnimationMap()
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

	BuildAnimationMap();
}

void UAirWidget::BuildAnimationMap()
{
	AnimationMap.Empty();

	UProperty* Prop = GetClass()->PropertyLink;

	while (Prop != nullptr)
	{
		if (Prop->GetClass() == UObjectProperty::StaticClass())
		{
			UObjectProperty* ObjProp = Cast<UObjectProperty>(Prop);

			if (ObjProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(this);
				UWidgetAnimation* WidgetAnim = Cast<UWidgetAnimation>(Obj);

				if (WidgetAnim && WidgetAnim->MovieScene)
				{
					FName AnimName = WidgetAnim->MovieScene->GetFName();
					AnimationMap.Add(AnimName, WidgetAnim);
				}
			}
		}

		Prop = Prop->PropertyLinkNext;
	}
}

UWidgetAnimation* UAirWidget::GetAnimationByName(const FName InKey)
{
	UWidgetAnimation* const* WidgetAnim = AnimationMap.Find(InKey);

	if (WidgetAnim)
	{
		return *WidgetAnim;
	}

	return nullptr;
}

void UAirWidget::OnBuild_Implementation()
{
}
