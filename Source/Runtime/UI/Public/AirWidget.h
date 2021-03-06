// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/UMG/Public/Blueprint/UserWidget.h>
#include <AirCore/Public/Core/AirHUD.h>

#include "AirWidget.generated.h"

class AAirChar;
class UAirInventory;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetClosed);

UCLASS(abstract, HideDropdown, MinimalAPI)
class UAirWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UAirWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = Build)
	virtual void Build();

	UFUNCTION(BlueprintNativeEvent, Category = Build)
	void OnBuild();

	UPROPERTY(EditDefaultsOnly, Category = DynamicOverlay)
	bool ShouldConsumeDynamicPanel;

public:

	UPROPERTY(BlueprintAssignable)
	FOnWidgetClosed OnWidgetClosed;

protected:

	virtual void NativeConstruct() override;

	UPROPERTY()
	AAirChar* LocalChar;

	bool NativeConstructCalled;
};
