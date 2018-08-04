// Fill out your copyright notice in the Description page of Project Settings.

#include "Container.h"
#include <ConstructorHelpers.h>
#include "AirController.h"
#include <Kismet/GameplayStatics.h>
#include <WidgetBlueprintLibrary.h>
#include "Utils/Functions/UMGFunctions.h"

AContainer::AContainer()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ContainerMesh"));
	RootComponent = Mesh;

	Inventory = CreateDefaultSubobject<UAirInventory>(TEXT("Inventory"));
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
					TransferUI->SetUserFocus(LocalController);
					LocalController->bShowMouseCursor = true;
					UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(LocalController, TransferUI, EMouseLockMode::LockAlways);
					
					TransferUI->AddToViewport(1);
				}
			}
		}
	}
}
