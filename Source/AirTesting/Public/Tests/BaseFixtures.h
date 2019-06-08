#include <AutomationTest.h>
#include <AutomationEditorCommon.h>
#include <Engine/World.h>
#include <AutomationCommon.h>
#include <Engine/Engine.h>
#include <EngineUtils.h>
#include <Engine/EngineTypes.h>

DEFINE_LOG_CATEGORY_STATIC(AutomationRunnerLog, Log, Log);

#define IMPLEMENT_AIRTEST(TestName, BaseClass, Category) IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(TestName, BaseClass, "Air." #Category "." #TestName, FAirBaseFixture::TestFlags)

#pragma optimize("", off)

#if WITH_DEV_AUTOMATION_TESTS

namespace BaseFixturePrivate
{
	const FName TestWorldName = TEXT("TestWorld");
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
	T* SpawnActor()
	{
		if (GameWorld)
		{
			T* NewActor = GameWorld->SpawnActor<T>(T::StaticClass());

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

#pragma optimize("", on)

#endif //WITH_DEV_AUTOMATION_TESTS