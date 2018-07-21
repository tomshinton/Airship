// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AirHUD.generated.h"

class UAirWidget;

UCLASS()
class AIRSHIP_API AAirHUD : public AHUD
{
	GENERATED_BODY()

	AAirHUD(const FObjectInitializer& ObjectInitializer);

public:

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void ToggleInventoryScreen();

	void SetIsAiming(const bool InIsAiming);

	UPROPERTY(EditDefaultsOnly, Category = Classes)
	TSubclassOf<UAirWidget> HUD;

	UPROPERTY(EditDefaultsOnly, Category = Classes)
	TSubclassOf<UAirWidget> InventoryScreen;

	UPROPERTY(EditDefaultsOnly, Category = Classes)
	TSubclassOf<UUserWidget> Crosshair;

protected:
	virtual void BeginPlay() override;

	TWeakObjectPtr<UAirWidget> HUDWidget;
	TWeakObjectPtr<UAirWidget> InventoryScreenWidget;
	TWeakObjectPtr<UUserWidget> CrosshairWidget;

	bool InventoryIsVisible;
	bool IsAiming;
};
