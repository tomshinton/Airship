#include <AutomationTest.h>

class FAirBaseFixture : public FAutomationTestBase
{
public:
	FAirBaseFixture(const FString& InName, const bool bInComplexTask)
		: FAutomationTestBase(InName, bInComplexTask) {}

	void TestPrint()
	{
		UE_LOG(LogTemp, Log, TEXT("Test"));
	}
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPlaceholderTestSimple, "Test.GivenSomeBullshit_WhenIClickRun_ItPasses", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::EngineFilter)
bool FPlaceholderTestSimple::RunTest(const FString& Parameters)
{
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FPlaceholderTestCustom, FAirBaseFixture, "Test.Test Custom", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::EngineFilter)
bool FPlaceholderTestCustom::RunTest(const FString& Parameters)
{
	TestPrint();
	return true;
}