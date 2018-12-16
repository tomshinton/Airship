// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AirHUD.generated.h"

class UUserWidget;
class UAirWidget;
class UAirHUDBase;

UCLASS()
class AIRSHIP_API AAirHUD : public AHUD
{
	GENERATED_BODY()

	AAirHUD(const FObjectInitializer& ObjectInitializer);

public:

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void ToggleInventoryScreen();

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void AddInventoryScreen(UUserWidget* InNewInventoryScreen, AAirController* InController);

	void SetIsAiming(const bool InIsAiming);

	UFUNCTION()
	void ReturnControlToHUD() const;

	UPROPERTY(EditDefaultsOnly, Category = Classes)
	TSubclassOf<UAirHUDBase> HUD;

	UPROPERTY(EditDefaultsOnly, Category = Classes)
	TSubclassOf<UAirWidget> InventoryScreen;

	UPROPERTY(EditDefaultsOnly, Category = Classes)
	TSubclassOf<UUserWidget> Crosshair;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UAirHUDBase* HUDWidget;

	UPROPERTY()
	UAirWidget* InventoryScreenWidget;

	UPROPERTY()
	UUserWidget* CrosshairWidget;

	bool InventoryIsVisible;
	bool IsAiming;

private:

	void ClearInventoryPanel();
};
