// Airship Project - Tom Shinton 2018

#include "Runtime/Item/Public/Container.h"

#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/Inventory/Public/InventoryComponent/AirInventory.h>
#include <Runtime/UI/Public/Utils/HUDTools.h>
#include <Runtime/UI/Public/Utils/UMGFunctions.h>
#include <Runtime/Utils/Public/Interface/InterfaceHelpers.h>

AContainer::AContainer()
: Mesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ContainerMesh")))
, Inventory(CreateDefaultSubobject<UAirInventory>(TEXT("ContainerInventory")))
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(Mesh);
}

void AContainer::OnInteract(AActor* InteractingActor)
{
	if (UWorld* World = GetWorld())
	{
		IInventoryInterface* OwningInventory = InterfaceHelpers::GetInterface<IInventoryInterface>(*this);
		IInventoryInterface* PlayerInventory = InterfaceHelpers::GetInterface<IInventoryInterface>(*InteractingActor);

		if(UTransferWindowBase* TransferUI = UTransferWindowBase::NewWindow(*OwningInventory, *PlayerInventory, *World))
		{				
			UHUDTools::AddToDynamicPanel(TransferUI, *this);
		}
	}
}
