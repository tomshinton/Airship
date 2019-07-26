// Airship Project - Tom Shinton 2018

#include "Runtime/Item/Public/WorldItem.h"
#include <Runtime/Inventory/Public/InventoryComponent/AirInventory.h>

const FName AWorldItem::BarrelSocketName = FName("BarrelSocket");

AWorldItem::AWorldItem()
	: ItemRoot(CreateDefaultSubobject<USceneComponent>(TEXT("ItemRoot")))
	, ItemMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh")))
{
	RootComponent = ItemRoot;
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetCastShadow(false);

	ItemMesh->SetCollisionProfileName("NoCollision");

}

void AWorldItem::StartPrimary()
{
}

void AWorldItem::EndPrimary()
{
}

void AWorldItem::StartSecondary()
{

}

void AWorldItem::EndSecondary()
{

}

void AWorldItem::StartWield()
{

}

void AWorldItem::EndWield()
{
	Destroy();
}

TOptional<FTransform> AWorldItem::GetBarrelTransform() const
{
	TArray<UActorComponent*> ActorComponents = GetComponentsByClass(USceneComponent::StaticClass());

	for (UActorComponent* ActorComp : ActorComponents)
	{
		if (USceneComponent* SceneComp = Cast<USceneComponent>(ActorComp))
		{
			if (SceneComp->DoesSocketExist(BarrelSocketName))
			{
				return SceneComp->GetSocketTransform(BarrelSocketName);
			}
		}
	}

	return TOptional<FTransform>();
}