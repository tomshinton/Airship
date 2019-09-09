// Airship Project - Tom Shinton 2018

#include "BaseFixtures.h"

#if WITH_DEV_AUTOMATION_TESTS

class FAirControllerTestFixture : public FAirBaseFixture
{

public:

	FAirControllerTestFixture(const FString& InName, const bool bInComplexTask)
		: FAirBaseFixture(InName, bInComplexTask) {}

	virtual void BeginTest()
	{
		FAirBaseFixture::BeginTest();
	}

	virtual void EndTest()
	{
		FAirBaseFixture::EndTest();
	}

};

#define IMPLEMENT_TEST(TestName) IMPLEMENT_AIRTEST(TestName, FAirControllerTestFixture, AirController)

#endif //WITH_DEV_AUTOMATION_TESTS
