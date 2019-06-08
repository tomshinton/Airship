// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WieldInterface.h"
#include "Utils/Datatypes/Inventory.h"

#include "AirInventory.generated.h"

class AWorldItem;

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSlotFocusUpdated, const int32);

UCLASS(MinimalAPI)
class UAirInventory : public UActorComponent
{
	GENERATED_BODY()

	UAirInventory();

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Name)
	FString InventoryName;
	
public:

	FInventory GetInventory() const { return Inventory; };

	UFUNCTION(BlueprintCallable, Category = Inventory)
	AIRCORE_API void AddItem(const FName& ID, const int32& Quantity);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	AIRCORE_API void RemoveItem(const FName& ID, const int32& Quantity);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	AIRCORE_API void TransferItem(const FName& ItemID, const int32& Quantity, UAirInventory* RemoveInventory);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Inventory)
	int32 GetInventorySize() const { return InventorySize; }

	UFUNCTION(BlueprintCallable, Category = Inventory)
	AIRCORE_API void Audit(const FName& ItemID, int32& Stack, int32& Total);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void SwapSlots(const int32& FirstSlot, const int32& SecondSlot);

	UFUNCTION(BlueprintPure, Category = Inventory)
	void GetBackpackBounds(bool& HasBackpackSlots, int32& BackpackStart, int32& BackpackEnd);

	UFUNCTION(BlueprintPure, Category = Inventory)
	void GetHotbarBounds(bool& HasHotbarSlots, int32& HotbarStart, int32& HotbarEnd);

	void SetHandComponents(USceneComponent* InLeftHand, USceneComponent* InRightHand) { RightHand = InRightHand; }

	UFUNCTION()
	void Reload();

	UFUNCTION()
	void ReduceCurrentClip(const int32 InAmountToReduce);

	AIRCORE_API FInventoryItem GetItemBySlot(const int32 ID);
	FName GetItemNameBySlot(const int32 ID);

	AIRCORE_API void SetItemBySlot(FInventoryItem InItem, const int32 InSlot);

	AIRCORE_API void UpdateFocus();
	AIRCORE_API void FocusNextItem();
	AIRCORE_API void FocusLastItem();

	int32 GetCurrentFocusedSlot() const { return CurrFocusedSlot; }

	void SetIsAiming(const bool InAiming) { IsAiming = InAiming; }
	bool GetIsAiming() const { return IsAiming; }

#if WITH_DEV_AUTOMATION_TESTS
	void SetCurrentFocusSlot(const int32 NewFocusedSlot) { CurrFocusedSlot = NewFocusedSlot; };
#endif //WITH_DEV_AUTOMATION_TESTS

	/************************************************************************/
	/* Interaction                                                          */
	/************************************************************************/

	void Wield();

	void StartPrimary();
	void EndPrimary();
	void StartSecondary();
	void EndSecondary();

	FOnInventoryUpdated OnInventoryUpdated;
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
	AWorldItem* CurrentWieldActor;

	USceneComponent* RightHand;

	bool IsAiming;
};
