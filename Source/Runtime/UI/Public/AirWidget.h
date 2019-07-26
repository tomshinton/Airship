// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Runtime/UMG/Public/Blueprint/UserWidget.h>
#include <AirCore/Public/Core/AirHUD.h>

#include "AirWidget.generated.h"

class AAirChar;
class UAirInventory;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetClosed);

UCLASS(abstract, MinimalAPI)
class UAirWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UAirWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = Build)
	virtual void Build();

	UFUNCTION(BlueprintNativeEvent, Category = Build)
	void OnBuild();

public:

	UPROPERTY(BlueprintAssignable)
	FOnWidgetClosed OnWidgetClosed;

protected:

	virtual void NativeConstruct() override;

	void BuildAnimationMap();
	UWidgetAnimation* GetAnimationByName(const FName InKey);

	UPROPERTY()
	AAirChar* LocalChar;

	UPROPERTY()
	TMap<FName, UWidgetAnimation*> AnimationMap;
};
