// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AirHUD.h"
#include "AirWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetClosed);

UCLASS()
class AIRSHIP_API UAirWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Build)
	virtual void Build();

	UFUNCTION(BlueprintNativeEvent, Category = Build)
	void OnBuild();

public:
	UFUNCTION(BlueprintPure, Category = HUD)
	AAirHUD* GetOwningHUD() const { return OwningHUD.Get(); }

	void SetOwningHUD(AAirHUD* InOwningHUD) { OwningHUD = InOwningHUD; }

	UPROPERTY(BlueprintAssignable)
	FOnWidgetClosed OnWidgetClosed;

protected:
	TWeakObjectPtr<AAirHUD> OwningHUD;
};
