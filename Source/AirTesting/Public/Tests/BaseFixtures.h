#include <AutomationTest.h>
#include <AutomationEditorCommon.h>
#include <Engine/World.h>
#include <AutomationCommon.h>
#include <Engine/Engine.h>

DEFINE_LOG_CATEGORY_STATIC(AutomationRunnerLog, Log, Log);

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
	
	virtual void BeginTest() override
	{
		UE_LOG(AutomationRunnerLog, Log, TEXT("BeginTest"));

		GameWorld = UWorld::CreateWorld(EWorldType::Game, true, BaseFixturePrivate::TestWorldName);
	}

	virtual void EndTest() override 
	{
		GameWorld = nullptr;
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

#endif //WITH_DEV_AUTOMATION_TESTS