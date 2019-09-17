// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/Inventory/Public/InventoryInterface.h"
#include "Runtime/Inventory/Public/InventoryTypes/CompoundInventory.h"
#include "Runtime/Inventory/Public/InventoryTypes/InventoryBag.h"

#include <Runtime/Item/Public/WieldInterface.h>

#include "AirInventory.generated.h"

class AWorldItem;

UCLASS(MinimalAPI)
class UAirInventory : public UActorComponent
	, public IInventoryInterface
{
	GENERATED_BODY()

	UAirInventory();

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Name)
	FString InventoryName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Bags)
	TArray<FInventoryBag> DefaultBags;

public:

	//IInventoryInterface
	virtual FOnInventoryUpdated& GetOnInventoryUpdated() override { return OnInventoryUpdated; };
	virtual FOnSlotFocusUpdated& GetOnSlotFocusUpdated() override { return OnSlotFocusUpdated; };
	virtual FOnInventoryInitialised& GetOnInventoryInitialised() override { return OnInventoryInitialised; };
	virtual CompoundInventory* GetInventory() override { return &Inventory; };
	virtual FInventoryItem GetItemBySlot(const FGuid& InBagID, const int32 InSlot) const;
	virtual FGuid GetBagIDByIndex(const int32 InIndex) const override;
	virtual FGuid GetFirstPrimaryBagID() const override;
	virtual const FInventoryBag* GetBagByType(const EBagType& InBagType) const override;
	virtual const FInventoryBag* GetBagByID(const FGuid& InBagID) const override;
	virtual int32 GetCurrentFocusedSlot() const override { return CurrFocusedSlot; };
	//~IInventoryInterface

	INVENTORY_API void AddBag(const FInventoryBag& InNewBag);

	void BroadcastUpdate();

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void AddItem(const FName& ID, const int32& Quantity);
	
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void RemoveItem(const FName& ID, const int32& Quantity);

	void SetHandComponents(USceneComponent* InLeftHand, USceneComponent* InRightHand) { RightHand = InRightHand; }
	
	UFUNCTION()
	INVENTORY_API void Reload();

	UFUNCTION()
	INVENTORY_API void ReduceCurrentClip(const int32 InAmountToReduce);

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
	FOnInventoryInitialised OnInventoryInitialised;

	virtual void BeginPlay() override;

private:

	CompoundInventory Inventory;

	int32 CurrFocusedSlot;

	UPROPERTY()
	AWorldItem* CurrentWieldActor;

	USceneComponent* RightHand;

	bool IsAiming;
};
