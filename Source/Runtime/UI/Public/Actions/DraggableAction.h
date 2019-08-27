// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/Actions/DraggableInterface.h"

#include <Runtime/CoreUObject/Public/UObject/ObjectMacros.h>
#include <Runtime/Engine/Public/TimerManager.h>

#if !UE_BUILD_SHIPPING
#include <Runtime/Core/Public/Logging/LogMacros.h>
#endif //!UE_BUILD_SHIPPING

class APlayerController;

class UInputComponent;
class UUserWidget;
class UWidgetTree;

DECLARE_LOG_CATEGORY_EXTERN(DraggableActionLog, All, All);

class FDraggableAction
{
public:

	FDraggableAction(UUserWidget& InParent);
	
	void Init(UInputComponent& InInputComponent);

protected:

	void StartDrag();
	void EndDrag();

	void DoMove();

private:

	void SetupDrag(const FDraggableHandle& InDraggableHandle);
	void SetTimerRate(const float InNewRate);

	UPROPERTY()
	UUserWidget* TargetWidget;

	UPROPERTY()
	UWidgetTree* TargetTree;

	UPROPERTY()
	UWorld* CachedWorld;

	UPROPERTY()
	APlayerController* CachedPlayerController;

	TOptional<FDraggableHandle> DraggableHandle;

	FTimerHandle MoveTimerHandle;
	FTimerDelegate MoveTimerDelegate;

	float MoveRate;
	float NonmoveRate;

	bool IsDragging;

	FVector2D InitialMouseOffset;
};