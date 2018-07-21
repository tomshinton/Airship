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

	UPROPERTY(EditDefaultsOnly, Category = Classes)
	TSubclassOf<UAirWidget> HUD;

	UPROPERTY(EditDefaultsOnly, Category = Classes)
	TSubclassOf<UAirWidget> InventoryScreen;

protected:
	virtual void BeginPlay() override;

	TWeakObjectPtr<UAirWidget> HUDWidget;
	TWeakObjectPtr<UAirWidget> InventoryScreenWidget;

	bool InventoryIsVisible;
};
