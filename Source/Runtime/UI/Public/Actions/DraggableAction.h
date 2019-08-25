// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/CoreUObject/Public/UObject/ObjectMacros.h>

#if !UE_BUILD_SHIPPING
#include <Runtime/Core/Public/Logging/LogMacros.h>
#endif //!UE_BUILD_SHIPPING

class UInputComponent;
class UUserWidget;

DECLARE_LOG_CATEGORY_EXTERN(DraggableActionLog, All, All);

class FDraggableAction
{
public:

	FDraggableAction(UUserWidget& InParent);
	
	void Init(UInputComponent& InInputComponent);

protected:

	void StartDrag();
	void EndDrag();

private:

	UPROPERTY()
	UUserWidget* ParentWidget;
};