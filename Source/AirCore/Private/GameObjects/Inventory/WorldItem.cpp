// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldItem.h"
#include "AirInventory.h"

const FName AWorldItem::BarrelSocketName = FName("BarrelSocket");

AWorldItem::AWorldItem()
{
	ItemRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ItemRoot"));
	RootComponent = ItemRoot;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
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
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
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