// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/Engine/Classes/GameFramework/Actor.h>
#include <Runtime/Item/Public/WieldInterface.h>

#include "WorldItem.generated.h"

class UAirInventory;
class UStaticMeshComponent;

UCLASS(MinimalAPI)
class AWorldItem : public AActor
	, public IWieldInterface
{
	GENERATED_BODY()
	
public:

	static const FName BarrelSocketName;

public:	

	AWorldItem();

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* ItemRoot;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ItemMesh;
	
public:

	//WieldInterface
	ITEM_API virtual void StartPrimary() override;
	ITEM_API virtual void EndPrimary() override;
	ITEM_API virtual void StartSecondary() override;
	ITEM_API virtual void EndSecondary() override;
	ITEM_API virtual void StartWield() override;
	ITEM_API virtual void EndWield() override;
	//~WieldInterface

	void SetAssociatedInventory(UAirInventory* InInventory) { AssociatedInventoryComponent = InInventory; }

protected:
	
	UPROPERTY()
	UAirInventory* AssociatedInventoryComponent;

	TOptional<FTransform> GetBarrelTransform() const;
};
