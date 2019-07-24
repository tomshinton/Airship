#include <AutomationTest.h>
#include <AutomationEditorCommon.h>
#include <Engine/World.h>
#include <AutomationCommon.h>
#include <Engine/Engine.h>
#include <EngineUtils.h>
#include <Engine/EngineTypes.h>


#include <Editor/UnrealEd/Classes/Editor/UnrealEdEngine.h>
#include "UnrealEdGlobals.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/WorldSettings.h"
#include "AirGameMode.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "LevelEditor.h"

DEFINE_LOG_CATEGORY_STATIC(AutomationRunnerLog, Log, Log);

#define IMPLEMENT_AIRTEST(TestName, BaseClass, Category) IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(TestName, BaseClass, "Air." #Category ".Unit." #TestName, FAirBaseFixture::TestFlags)
#define IMPLEMENT_AIRMAPTEST(TestName, BaseClass, Category) IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(TestName, BaseClass, "Air." #Category ".Map." #TestName, FAirBaseFixture::TestFlags)

#pragma optimize("", off)

#if WITH_DEV_AUTOMATION_TESTS

namespace BaseFixturePrivate
{
	const FName TestWorldName = TEXT("TestWorld");
	const FString TestLevelName = "/Game/Tests/MapTests/TestMap.TestMap";
}

class FAirBaseFixture : public FAutomationTestBase
{

public:

	FAirBaseFixture(const FString& InName, const bool bInComplexTask)
		: FAutomationTestBase(InName, bInComplexTask)
	{}
	
	UWorld* CreateTestWorld(const FName& UniqueWorldName, EWorldType::Type WorldType)
	{
		FWorldContext& WorldContext = GEngine->CreateNewWorldContext(WorldType);
		UWorld* NewWorld = UWorld::CreateWorld(WorldType, false, UniqueWorldName);
		WorldContext.SetCurrentWorld(NewWorld);

		return NewWorld;
	}
	
	void DestroyTestWorld()
	{
		if (GameWorld->AreActorsInitialized())
		{
			for (AActor* const Actor : FActorRange(GameWorld))
			{
				if (Actor)
				{
					Actor->RouteEndPlay(EEndPlayReason::LevelTransition);
				}
			}
		}

		GEngine->ShutdownWorldNetDriver(GameWorld);
		const bool bInformEngine = true;
		GameWorld->DestroyWorld(bInformEngine);
		GameWorld->SetPhysicsScene(nullptr);
		GEngine->DestroyWorldContext(GameWorld);

		GameWorld = nullptr;
	}

	virtual void BeginTest() override
	{
		UE_LOG(AutomationRunnerLog, Log, TEXT("BeginTest"));

		GameWorld = CreateTestWorld(TEXT("TestWorld"), EWorldType::Game);
	}

	virtual void EndTest() override 
	{
		UE_LOG(AutomationRunnerLog, Log, TEXT("EndTest"));
		DestroyTestWorld();
	}

	template<class T>
	T* SpawnActor(UWorld* WorldOverride = nullptr)
	{
		UWorld* WorldToUse = GameWorld;

		if (WorldOverride)
		{
			WorldToUse = WorldOverride;
		}

		if (WorldToUse)
		{
			T* NewActor = WorldToUse->SpawnActor<T>(T::StaticClass());

			if (NewActor)
			{
				SpawnedActors.Add(NewActor);
				return NewActor;
			}

			UE_LOG(AutomationRunnerLog, Error, TEXT("Could not spawn actor in AirBaseFixture"));
			return nullptr;
		}

		return nullptr;
	}

	TArray<AActor*> SpawnedActors;
	UWorld* GameWorld;

	static const int TestFlags = EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter;
};


class FAirMapTestFixture : public FAutomationTestBase
{
public:

	FAirMapTestFixture(const FString& InName, const bool bInComplexTask)
		: FAutomationTestBase(InName, bInComplexTask)
	{}

	virtual void BeginTest() override
	{
		FAutomationEditorCommonUtils::LoadMap(BaseFixturePrivate::TestLevelName);

		FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
		TSharedPtr<class ILevelViewport> ActiveLevelViewport = LevelEditorModule.GetFirstActiveViewport();

		GUnrealEd->RequestPlaySession(false, ActiveLevelViewport, false, NULL, NULL, -1, false);
	}

	virtual void EndTest() override 
	{
		//GUnrealEd->RequestEndPlayMap();
	}

	virtual TSubclassOf<AGameMode> GetGameMode()
	{
		return AAirGameMode::StaticClass();
	}

	static ACharacter* GetLocalCharacter(UWorld* World)
	{
		if (GWorld && GWorld->GetFirstPlayerController())
		{
			return Cast<ACharacter>(GWorld->GetFirstPlayerController()->GetPawn());
		}

		return nullptr;
	}

	static APlayerController* GetLocalPlayerController(UWorld* World)
	{
		if (World)
		{
			return World->GetFirstPlayerController();
		}

		return nullptr;
	}
};

#pragma optimize("", on)

#endif //WITH_DEV_AUTOMATION_TESTS