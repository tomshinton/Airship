// Airship Project - Tom Shinton 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ComponentProviderInterface.h"

#include "AirChar.generated.h"

class UCameraComponent;
class UAirInventory;
class UAirMovementComponent;
class UInteractionComponent;
class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharLanded);

UCLASS(MinimalAPI)
class AAirChar : public ACharacter
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	// Sets default values for this character's properties
	AAirChar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hands)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hands)
	USceneComponent* RightHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hands)
	USceneComponent* LeftHand;

	UPROPERTY(EditDefaultsOnly, Category = Hands)
	float HandBlendTime;

	UPROPERTY(EditDefaultsOnly, Category = Hands)
	float HandOffset;

	UPROPERTY()
	UHealthComponent* HealthComponent;

	UPROPERTY()
	UAirMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly)
	UAirInventory* InventoryComponent;

	FOnCharLanded OnCharLanded;

	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintPure, Category = Inventory)
	UAirInventory* GetInventory() const { return InventoryComponent; };

	UInputComponent* GetCachedInputComponent() const {return CachedInputComponent; };

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FTransform RightHandTargetTransform;
	FVector LeftHandTargetLocation;	

private:

	void DeferUIBinding(UInputComponent* PlayerInputComponent);

	bool ShouldLowerHands();

	UPROPERTY()
	UInputComponent* CachedInputComponent;

	//Testing
	UPROPERTY()
	UWorld* CachedWorld;
};
