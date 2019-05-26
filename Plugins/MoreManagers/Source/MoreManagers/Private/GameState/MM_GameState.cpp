// Airship Project - Tom Shinton 2018

#include "MM_GameState.h"

#include "MoreManagers/Public/ManagerCore/ManagerComponent.h"

namespace
{
	namespace GameStateComponentNames
	{
		const FName ManagerComponentName = TEXT("ManagerComponent");
	}
}

AMM_GameState::AMM_GameState()
	: ManagerComponent(CreateDefaultSubobject<UManagerComponent>(GameStateComponentNames::ManagerComponentName))
{
}

void AMM_GameState::BeginPlay()
{
	Super::BeginPlay();

	if (ManagerComponent)
	{
		if (UWorld* World = GetWorld())
		{
			ManagerComponent->SetCachedWorld(World);
			ManagerComponent->SpinupManager();
		}
	}
}

