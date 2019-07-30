// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/Inventory/Public/InventoryInterface.h"
#include "Runtime/Inventory/Public/HotbarInterface.h"
#include "Runtime/Inventory/Public/InventoryTypes/Inventory.h"

#include <Runtime/Item/Public/WieldInterface.h>
#include "AirInventory.generated.h"

class AWorldItem;

UCLASS(MinimalAPI)
class UAirInventory : public UActorComponent
	, public IInventoryInterface
	, public IHotbarInterface
{
	GENERATED_BODY()

	UAirInventory();

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Name)
	FString InventoryName;
	
public:

	//IInventoryInterface
	virtual FOnInventoryUpdated& GetOnInventoryUpdated() override { return OnInventoryUpdated; };
	virtual FOnSlotFocusUpdated& GetOnSlotFocusUpdated() override { return OnSlotFocusUpdated; };
	virtual FInventory& GetInventory() override { return Inventory; };
	virtual int32 GetCurrentFocusedSlot() const override { return CurrFocusedSlot; }

	virtual FInventoryItem GetItemBySlot(const int32 InSlot) const;
	virtual void SetItemBySlot(const FInventoryItem& InItem, const int32 InSlot) override;

	virtual int32 GetInventorySlotCount() const override { return InventorySize; };
	//~IInventoryInterface

	//IHotbarInterface
	virtual int32 GetNumHotbarSlots() const override { return HotbarSlots; };
	//~IHotbarInterface

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void AddItem(const FName& ID, const int32& Quantity);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void RemoveItem(const FName& ID, const int32& Quantity);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void TransferItem(const FName& ItemID, const int32& Quantity, UAirInventory* RemoveInventory);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Inventory)
	int32 GetInventorySize() const { return InventorySize; }

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void SwapSlots(const int32& FirstSlot, const int32& SecondSlot);

	UFUNCTION(BlueprintPure, Category = Inventory)
	void GetBackpackBounds(bool& HasBackpackSlots, int32& BackpackStart, int32& BackpackEnd);

	UFUNCTION(BlueprintPure, Category = Inventory)
	void GetHotbarBounds(bool& HasHotbarSlots, int32& HotbarStart, int32& HotbarEnd);

	void SetHandComponents(USceneComponent* InLeftHand, USceneComponent* InRightHand) { RightHand = InRightHand; }
	
	UFUNCTION()
	INVENTORY_API void Reload();

	UFUNCTION()
	INVENTORY_API void ReduceCurrentClip(const int32 InAmountToReduce);

	FName GetItemNameBySlot(const int32& ID) const;

	INVENTORY_API void SetItemBySlot(FInventoryItem InItem, const int32 InSlot);

	void UpdateFocus();
	INVENTORY_API void FocusNextItem();
	INVENTORY_API void FocusLastItem();


	void SetIsAiming(const bool InAiming) { IsAiming = InAiming; }
	bool GetIsAiming() const { return IsAiming; }

#if WITH_DEV_AUTOMATION_TESTS
	void SetCurrentFocusSlot(const int32 NewFocusedSlot) { CurrFocusedSlot = NewFocusedSlot; };
#endif //WITH_DEV_AUTOMATION_TESTS

	void Wield();

	INVENTORY_API void StartPrimary();
	INVENTORY_API void EndPrimary();
	INVENTORY_API void StartSecondary();
	INVENTORY_API void EndSecondary();

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
