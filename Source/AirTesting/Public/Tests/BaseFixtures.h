#include <AutomationTest.h>
#include <AutomationEditorCommon.h>
#include <Engine/World.h>
#include <AutomationCommon.h>
#include <Engine/Engine.h>

DEFINE_LOG_CATEGORY_STATIC(AutomationRunnerLog, Log, Log);

#if WITH_DEV_AUTOMATION_TESTS

class FAirBaseFixture : public FAutomationTestBase
{

public:

	FAirBaseFixture(const FString& InName, const bool bInComplexTask)
		: FAutomationTestBase(InName, bInComplexTask)
	{}
	
	template<class T>
	T* SpawnActor()
	{
		if (GetTestWorld())
		{
			T* NewActor = GetTestWorld()->SpawnActor<T>(T::StaticClass());

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

	void CleanUp()
	{
		for (AActor* SpawnedActor : SpawnedActors)
		{
			SpawnedActor->Destroy();
		}

		SpawnedActors.Empty();
	}

	static UWorld* GetTestWorld()
	{
		UWorld* TestWorld = nullptr;
		const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
		for (const FWorldContext& Context : WorldContexts)
		{
			if(Context.World() != nullptr)
			{
				TestWorld = Context.World();
				break;
			}
		}

		return TestWorld;
	}

	TArray<AActor*> SpawnedActors;

	static const int TestFlags = EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter;
};

#endif //WITH_DEV_AUTOMATION_TESTS