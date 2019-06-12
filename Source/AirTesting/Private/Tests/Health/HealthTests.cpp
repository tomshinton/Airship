#include "BaseFixtures.h"
#include "HealthComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

#if WITH_DEV_AUTOMATION_TESTS

class FHealthTestFixture : public FAirBaseFixture
{

public:

	FHealthTestFixture(const FString& InName, const bool bInComplexTask)
		: FAirBaseFixture(InName, bInComplexTask) {}

	virtual void BeginTest()
	{
		FAirBaseFixture::BeginTest();

		ACharacter* TestCharacter = SpawnActor<ACharacter>();
		HealthComponent = NewObject<UHealthComponent>(TestCharacter);

		HealthInterface = Cast<IHealthInterface>(HealthComponent);
	}

	virtual void EndTest()
	{
		FAirBaseFixture::EndTest();

		if (HealthComponent)
		{
			HealthComponent = nullptr;
		}
	}

	UHealthComponent* HealthComponent;
	IHealthInterface* HealthInterface;
};

#define IMPLEMENT_TEST(TestName) IMPLEMENT_AIRTEST(TestName, FHealthTestFixture, AirHealthComponent)

IMPLEMENT_TEST(FApplyDamageCalled_ValidChangeEvent_HealthChangedEventCalled)
bool FApplyDamageCalled_ValidChangeEvent_HealthChangedEventCalled::RunTest(const FString& Parameters)
{
	const FBaseDamageEvent NewEvent(1.f, EDamageType::Falling, nullptr);
	bool CallbackSuccess = false;

	HealthInterface->GetOnHealthChangedEvent().AddLambda([this, &NewEvent, &CallbackSuccess](const FBaseDamageEvent& InEvent)
	{
		if (InEvent == NewEvent)
		{
			CallbackSuccess = true;
		}
	});

	HealthInterface->ApplyDamage(NewEvent);

	return CallbackSuccess;
}

IMPLEMENT_TEST(FApplyDamageCalled_CorrectEventInDamageHistory)
bool FApplyDamageCalled_CorrectEventInDamageHistory::RunTest(const FString& Parameters)
{
	const FBaseDamageEvent NewEvent(1.f, EDamageType::Falling, nullptr);

	HealthInterface->ApplyDamage(NewEvent);

	TestTrue(TEXT("Expected the HealthHistory to contain the damage event"), HealthComponent->GetDamageHistory().Contains(NewEvent));

	return true;
}

IMPLEMENT_TEST(FApplyDamageCalled_DamageEventExceedsHistoryLength_EventPoppedFromArray)
bool FApplyDamageCalled_DamageEventExceedsHistoryLength_EventPoppedFromArray::RunTest(const FString& Parameters)
{
	const FBaseDamageEvent FirstEvent(1.f, EDamageType::Falling, nullptr);
	const FBaseDamageEvent SecondEvent(2.f, EDamageType::Falling, nullptr);

	HealthComponent->SetDamageHistoryLimit(1);

	HealthInterface->ApplyDamage(FirstEvent);
	TestTrue(TEXT("Expected the HealthHistory to contain the damage event"), HealthComponent->GetDamageHistory().Contains(FirstEvent));

	HealthInterface->ApplyDamage(SecondEvent);

	TestFalse(TEXT("Expected the HealthHistory to now longer contain the first damage event"), HealthComponent->GetDamageHistory().Contains(FirstEvent));

	return true;
}

IMPLEMENT_TEST(FApplyDamageCalled_DamageEventAmountExceedsMaxHealth_HealthDepletedEventCalled)
bool FApplyDamageCalled_DamageEventAmountExceedsMaxHealth_HealthDepletedEventCalled::RunTest(const FString& Parameters)
{
	HealthComponent->ResetToNewMaxHealth(1.f);

	const FBaseDamageEvent NewEvent(10.f, EDamageType::Flat, nullptr);
	bool CallbackSuccess = false;

	HealthInterface->GetOnHealthDepletedEvent().AddLambda([this, &NewEvent, &CallbackSuccess](const FBaseDamageEvent& InEvent)
	{
		if (InEvent == NewEvent)
		{
			CallbackSuccess = true;
		}
	});

	HealthInterface->ApplyDamage(NewEvent);

	return CallbackSuccess;
}

IMPLEMENT_TEST(FApplyDamageCalled_FallingDamageType_AmountModifiedByCurve)
bool FApplyDamageCalled_FallingDamageType_AmountModifiedByCurve::RunTest(const FString& Parameters)
{
	UCurveFloat* NewCurve = NewObject<UCurveFloat>();
	NewCurve->FloatCurve.AddKey(0.f, 0.f);
	NewCurve->FloatCurve.AddKey(1.f, 1.f);

	HealthComponent->SetFallDamageCurve(NewCurve);

	ACharacter* OwningCharacter = Cast<ACharacter>(HealthComponent->GetOwner());
	OwningCharacter->GetMovementComponent()->Velocity = FVector(0.f, 0.f, -HealthComponent->GetMaxSupportedVelocity() *0.5);

	const FBaseDamageEvent NewEvent(10.f, EDamageType::Falling, nullptr);
	bool CallbackSuccess = false;

	HealthInterface->GetOnHealthChangedEvent().AddLambda([this, &NewEvent, &CallbackSuccess](const FBaseDamageEvent& InEvent)
	{
		if (!FMath::IsNearlyEqual(InEvent.Amount, NewEvent.Amount))
		{
			CallbackSuccess = true;
		}
	});

	HealthInterface->ApplyDamage(NewEvent);

	return CallbackSuccess;
}

#endif //WITH_DEV_AUTOMATION_TESTS
