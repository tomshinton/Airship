// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Datatypes/InventoryItems.h"
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
	void AddItem(const int32 ID, const int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void RemoveItem(const int32 ID, const int32 Quantity);

	FInventoryItem GetItemByID(const int32 ID);

	void FocusNextItem();
	void FocusLastItem();

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnSlotFocusUpdated OnSlotFocusUpdated;

	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	FInventory Inventory;

	int32 CurrFocusedSlot;
	int32 HotbarSlots;
};
