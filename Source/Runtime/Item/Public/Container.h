// Airship Project - Tom Shinton 2018

#pragma once

#include <AirCore/Public/Interfaces/InteractableInterface.h>
#include <Runtime/UI/Public/Widgets/Inventory/TransferWindowBase.h>

#include "Container.generated.h"

//////////////////////////////////////////////////////////////////////////
// Base class for all containers, so barrels, chests, lockboxes, etc.
//////////////////////////////////////////////////////////////////////////

class UStaticMeshComponent;
class UAirInventory;

UCLASS()
class AContainer : public AActor,
	public IInteractableInterface
{
	GENERATED_BODY()
	
public:	

	AContainer();	

	UPROPERTY(EditDefaultsOnly, Category = UI)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	UAirInventory* Inventory;

protected:

	//InteractableInterface
	virtual void OnInteract(AActor* InteractingActor) override;
	virtual FText GetDisplayName() const override { return FText::FromString(TEXT("Container")); };
	//~InteractableInterface
};
