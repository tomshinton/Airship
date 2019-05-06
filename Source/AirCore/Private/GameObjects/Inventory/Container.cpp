// Fill out your copyright notice in the Description page of Project Settings.

#include "Container.h"
#include <ConstructorHelpers.h>
#include "AirController.h"
#include <Kismet/GameplayStatics.h>
#include <WidgetBlueprintLibrary.h>
#include "Utils/Functions/UMGFunctions.h"

AContainer::AContainer()
	: Mesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ContainerMesh")))
	, Inventory(CreateDefaultSubobject<UAirInventory>(TEXT("Inventory")))
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = Mesh;
}

void AContainer::OnInteract(AActor* InteractingActor)
{
	if (TransferWidget)
	{
		if (UWorld* World = GetWorld())
		{
			if (UTransferWindowBase* TransferUI = Cast<UTransferWindowBase>(CreateWidget<UTransferWindowBase>(World, TransferWidget)))
			{
				UAirInventory* InteractingUI = Cast<UAirInventory>(InteractingActor->GetComponentByClass(UAirInventory::StaticClass()));
				TransferUI->SetAppropriateInventories(Inventory, InteractingUI);
				
				if (AAirController* LocalController = Cast<AAirController>(UGameplayStatics::GetPlayerController(World, 0)))
				{

				}
			}
		}
	}
}
