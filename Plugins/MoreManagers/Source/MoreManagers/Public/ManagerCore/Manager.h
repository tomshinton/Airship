// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

class UManagerComponent;

#include "Manager.generated.h"

UCLASS(Blueprintable)
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

protected:

	UPROPERTY(EditDefaultsOnly, Category = Tick)
	bool IsTickEnabled;

	UPROPERTY(EditDefaultsOnly, Category = Tick, meta = (EditCondition = IsTickEnabled))
	float TickFrequency;

	UPROPERTY(EditDefaultsOnly, Category = Instantiation)
	bool ShouldDeferCompleteCallback;

	UFUNCTION(BlueprintPure, Category = Tick)
	bool GetIsTickEnabled() const;

	UFUNCTION(BlueprintPure, Category = Tick)
	float GetDeltaTime();

	UFUNCTION(BlueprintPure, Category = Tick)
	UWorld* GetWorld() const;

	virtual void Tick();

	float CachedDeltaTime;

private:

	virtual void Start(const TFunction<void()>& OnSetupCompleteCallback, UWorld* const WorldContext);

	void BeginTick();

	bool bHasBeganStart;

	FTimerHandle TickHandle;
	TFunction<void()> SetupCompleteCallback;

	UPROPERTY()
	UWorld* CachedWorld;

	float TimeOfLastTick;
};