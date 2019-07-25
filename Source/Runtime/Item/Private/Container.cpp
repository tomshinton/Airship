// Airship Project - Tom Shinton 2018

#include "Runtime/Item/Public/Container.h"

#include <AirCore/Utils/Functions/UMGFunctions.h>
#include <AirCore/Public/Core/AirController.h>
#include <AirCore/Public/Core/GameSettings/UISettings.h>
#include <Runtime/Inventory/Public/InventoryComponent/AirInventory.h>
#include <Runtime/UI/Public/Utils/HUDTools.h>

AContainer::AContainer()
	: Mesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ContainerMesh")))
	, Inventory(CreateDefaultSubobject<UAirInventory>(TEXT("Inventory")))
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = Mesh;
}

void AContainer::OnInteract(AActor* InteractingActor)
{
	if (UUISettings* UISettings = UUISettings::Get())
	{
		if (UWorld* World = GetWorld())
		{
			if (UTransferWindowBase* TransferUI = Cast<UTransferWindowBase>(CreateWidget<UTransferWindowBase>(World, UISettings->TransferWindowClass)))
			{
				UAirInventory* InteractingInventory = Cast<UAirInventory>(InteractingActor->GetComponentByClass(UAirInventory::StaticClass()));
				
				if (AAirController* LocalController = Cast<AAirController>(UGameplayStatics::GetPlayerController(World, 0)))
				{
					UHUDTools::AddToDynamicPanel(TransferUI, *this);
				}
			}
		}
	}
}
