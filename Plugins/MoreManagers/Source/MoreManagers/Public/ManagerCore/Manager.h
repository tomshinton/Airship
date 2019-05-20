// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

class UManagerComponent;

#include "Manager.generated.h"

UCLASS(Blueprintable, Abstract)
class MOREMANAGERS_API UManager : public UObject
{
	GENERATED_BODY()

	friend UManagerComponent;

public:

	UManager();
	
	UFUNCTION(BlueprintImplementableEvent, Category = Flow)
	void OnTick(const float& DeltaTime);

	UFUNCTION(BlueprintImplementableEvent, Category = Flow)
	void OnStart();

	UFUNCTION(BlueprintCallable, Category = Instantiation)
	void SetupComplete();

private:

	virtual void Start(const TFunction<void()>& OnSetupCompleteCallback);
	virtual void Tick();

	TFunction<void()> SetupCompleteCallback;

	UPROPERTY(EditDefaultsOnly, Category = Instantiation)
	bool ShouldDeferCompleteCallback;

	UFUNCTION(BlueprintPure, Category = Tick)
	bool GetIsTickEnabled() const;

	UPROPERTY(EditDefaultsOnly, Category = Tick)
	bool IsTickEnabled;

	UPROPERTY(EditDefaultsOnly, Category = Tick, meta = (EditCondition = IsTickEnabled))
	float TickFrequency;
};