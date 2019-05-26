// Airship Project - Tom Shinton 2018

#pragma once

#include "GameFramework/GameState.h"
#include "MM_GameState.generated.h"

class UManagerComponent;

UCLASS()
class MOREMANAGERS_API AMM_GameState : public AGameState
{
	GENERATED_BODY()

	AMM_GameState();
	
	virtual void BeginPlay() override;

public:

	UPROPERTY()
	UManagerComponent* ManagerComponent;
};
