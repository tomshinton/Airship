#include <AutomationTest.h>
#include <AutomationEditorCommon.h>
#include <Engine\World.h>

DEFINE_LOG_CATEGORY_STATIC(AutomationRunnerLog, Log, Log);

class FAirBaseFixture : public FAutomationTestBase
{
public:

	FAirBaseFixture(const FString& InName, const bool bInComplexTask)
		: FAutomationTestBase(InName, bInComplexTask) {}
	
	template<class T>
	T* SpawnActor()
	{
		if (UWorld* World = FAutomationEditorCommonUtils::CreateNewMap())
		{
			T* NewActor = World->SpawnActor<T>(AActor::StaticClass());

			if (NewActor)
			{
				return NewActor;
			}

			UE_LOG(AutomationRunnerLog, Error, TEXT("Could not spawn actor in AirBaseFixture"));
			return nullptr;
		}

		return nullptr;
	}

	static const int TestFlags = EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter;
};