// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WieldInterface.h"
#include <Components/StaticMeshComponent.h>
#include "WorldItem.generated.h"

UCLASS()
class AIRSHIP_API AWorldItem : public AActor, public IWieldInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldItem();

	UPROPERTY(EditDefaultsOnly)
		USceneComponent* ItemRoot;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ItemMesh;

public:
	//Start WieldInterface
	virtual void StartPrimary() override;
	virtual void EndPrimary() override;
	virtual void StartSecondary() override;
	virtual void EndSecondary() override;
	virtual void StartWield() override;
	virtual void EndWield() override;
	//End WieldInterface
};
