#include "BaseFixtures.h"
#include "AirController.h"
#include "InteractionComponent.h"
#include "TimerManager.h"
#include "AirChar.h"
#include "InteractableMock.h"
#include "AutomationEditorCommon.h"

#if WITH_DEV_AUTOMATION_TESTS

class FInteractionComponentTestFixture : public FAirBaseFixture
{

public:

	FInteractionComponentTestFixture(const FString& InName, const bool bInComplexTask)
		: FAirBaseFixture(InName, bInComplexTask) {}

	virtual void BeginTest()
	{
		FAirBaseFixture::BeginTest();

		AirChar = SpawnActor<AAirChar>();
		AAirController* TestController = SpawnActor<AAirController>();

		TestController->SetPawn(AirChar);
		AirChar->PossessedBy(TestController);

		InteractionComponent = NewObject<UInteractionComponent>(TestController);
		InteractionComponent->RegisterComponent();
	}

	virtual void EndTest()
	{
		FAirBaseFixture::EndTest();
	}

	FVector GetLocationInfrontOfPlayer(const float Distance) const
	{
		if (AirChar)
		{
			FVector ForwardDirection = AirChar->GetActorForwardVector();

			return AirChar->GetActorLocation() + (ForwardDirection * Distance);
		}

		return FVector::ZeroVector;
	}

	AAirChar* AirChar;
	UInteractionComponent* InteractionComponent;
};

#define IMPLEMENT_TEST(TestName) IMPLEMENT_AIRTEST(TestName, FInteractionComponentTestFixture, InteractionComponent)
#define IMPLEMENT_MAPTEST(TestName) IMPLEMENT_AIRMAPTEST(TestName, FAirMapTestFixture, InteractionComponent)

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FWaitForAsyncInteractionTrace, UInteractionComponent*, InteractionComponent);
bool FWaitForAsyncInteractionTrace::Update()
{
	if (UWorld* World = GWorld)
	{
		for (AActor* CurrentActor : FActorRange(World))
		{
			if (AAirChar* AirChar = Cast<AAirChar>(CurrentActor))
			{
				return true;
			}
		}
		return false;
	}

	return true;
	//return InteractionComponent->GetLastKnownTransform().IsSet();
}

IMPLEMENT_TEST(FValidInteractionComponent_BeginPlayCalled_ValidControllingOwner_WorldCached)
bool FValidInteractionComponent_BeginPlayCalled_ValidControllingOwner_WorldCached::RunTest(const FString& Parameters)
{
	InteractionComponent->BeginPlay();

	TestTrue(TEXT("Expected the CachedWorld to be valid"), InteractionComponent->GetCachedWorld() != nullptr);

	return true;
}

IMPLEMENT_TEST(FValidInteractionComponent_BeginPlayCalled_CachedTraceParamsBuilt)
bool FValidInteractionComponent_BeginPlayCalled_CachedTraceParamsBuilt::RunTest(const FString& Parameters)
{
	InteractionComponent->BeginPlay();

	FCollisionQueryParams& CachedParams = InteractionComponent->GetCachedTraceParams();

	//If we've tagged this, its fair to assume we've built and cached the struct
	TestTrue(TEXT("Expected the CachedParams to have been built and cached in InteractionComponent"), CachedParams.TraceTag != "");

	return true;
}
	
IMPLEMENT_TEST(FValidInteractionComponent_BeginPlayCalled_OnLookOverDelegateBound)
bool FValidInteractionComponent_BeginPlayCalled_OnLookOverDelegateBound::RunTest(const FString& Parameters)
{
	InteractionComponent->BeginPlay();

	FTraceDelegate& InteractionComponentTraceDelegate = InteractionComponent->GetOnLookOverDelegate();

	TestTrue(TEXT("Expected OnLookAtDelegate to have been bound"), InteractionComponentTraceDelegate.IsBound());

	return true;
}

IMPLEMENT_TEST(FValidInteractionComponent_AsyncTraceOver_OnLookOverFunctionCalled)
bool FValidInteractionComponent_AsyncTraceOver_OnLookOverFunctionCalled::RunTest(const FString& Parameters)
{
	InteractionComponent->BeginPlay();

	FTraceDelegate& InteractionComponentTraceDelegate = InteractionComponent->GetOnLookOverDelegate();

	InteractionComponent->ForceLook();

	GameWorld->Tick(ELevelTick::LEVELTICK_All, InteractionComponent->GetLookAtFrequency() + KINDA_SMALL_NUMBER);

	return true;
}

IMPLEMENT_MAPTEST(FValidInteractionComponent_LookAtTraceExecuted_InteractableInfrontOfPlayerAndInTraceRangeItemDetected)
bool FValidInteractionComponent_LookAtTraceExecuted_InteractableInfrontOfPlayerAndInTraceRangeItemDetected::RunTest(const FString& Parameters)
{
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncInteractionTrace(nullptr));

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS
