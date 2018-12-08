// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utils/Datatypes/InventoryItems.h"
#include "WieldInterface.h"

#include "AirInventory.generated.h"

class AWorldItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotFocusUpdated, const int32, Slot);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIRSHIP_API UAirInventory : public UActorComponent
{
	GENERATED_BODY()

	UAirInventory();

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Name)
	FString InventoryName;
	
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

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void SwapSlots(const int32 FirstSlot, const int32 SecondSlot);

	UFUNCTION(BlueprintPure, Category = Inventory)
	void GetBackpackBounds(bool& HasBackpackSlots, int32& BackpackStart, int32& BackpackEnd);

	UFUNCTION(BlueprintPure, Category = Inventory)
	void GetHotbarBounds(bool& HasHotbarSlots, int32& HotbarStart, int32& HotbarEnd);

	void SetHandComponents(USceneComponent* InLeftHand, USceneComponent* InRightHand) { RightHand = InRightHand; }

	UFUNCTION()
	void Reload();

	UFUNCTION()
	void ReduceCurrentClip(const int32 InAmountToReduce);

	FInventoryItem GetItemBySlot(const int32 ID);
	FName GetItemNameBySlot(const int32 ID);

	void SetItemBySlot(FInventoryItem InItem, const int32 InSlot);

	void FocusNextItem();
	void FocusLastItem();

	int32 GetCurrentFocusedSlot() const { return CurrFocusedSlot; }

	void SetIsAiming(const bool InAiming) { IsAiming = InAiming; }
	bool GetIsAiming() const { return IsAiming; }

	/************************************************************************/
	/* Interaction                                                          */
	/************************************************************************/

	void Wield();

	void StartPrimary();
	void EndPrimary();
	void StartSecondary();
	void EndSecondary();

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnSlotFocusUpdated OnSlotFocusUpdated;

	UPROPERTY(EditDefaultsOnly)
	int32 InventorySize;

	UPROPERTY(EditDefaultsOnly)
	int32 HotbarSlots;

	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	FInventory Inventory;

	int32 CurrFocusedSlot;

	UPROPERTY()
	TWeakObjectPtr<AWorldItem> CurrentWieldActor;

	USceneComponent* RightHand;

	bool IsAiming;
};
