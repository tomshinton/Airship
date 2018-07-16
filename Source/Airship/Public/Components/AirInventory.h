// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utils/Datatypes/InventoryItems.h"
#include "WieldInterface.h"

#include "AirInventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotFocusUpdated, const int32, Slot);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIRSHIP_API UAirInventory : public UActorComponent
{
	GENERATED_BODY()

	UAirInventory();

public:
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void AddItem(const FName ID, const int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void RemoveItem(const FName ID, const int32 Quantity);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Inventory)
	int32 GetInventorySize() const { return InventorySize; }

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void TransferItem(FName ItemID, int32 Quantity, UAirInventory* RemoveInventory);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void Audit(FName ItemID, int32& Stacks, int32& Total);

	void SetHandComponents(USceneComponent* InLeftHand, USceneComponent* InRightHand) {	LeftHand = InLeftHand; RightHand = InRightHand;	}

	FInventoryItem GetItemBySlot(const int32 ID);
	FName GetItemNameBySlot(const int32 ID);

	void FocusNextItem();
	void FocusLastItem();

	void Wield();

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void PrintInventory();

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnSlotFocusUpdated OnSlotFocusUpdated;

	UPROPERTY(EditDefaultsOnly)
	int32 InventorySize;

	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	FInventory Inventory;

	int32 CurrFocusedSlot;
	int32 HotbarSlots;

	IWieldInterface* CurrentWieldInterface;

	USceneComponent* RightHand;
	USceneComponent* LeftHand;
};
