// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/CoreUObject/Public/UObject/Interface.h>
#include "UserWidget.h"
#include "Widget.h"

#include "DraggableInterface.generated.h"

//class UWidget;
//class UUserWidget;

USTRUCT()
struct FDraggableHandle
{
	GENERATED_BODY()

public:

	FDraggableHandle()
		: DraggableWidget(nullptr)
		, Handle(nullptr)
	{}

	FDraggableHandle(UUserWidget* InDraggableWidget, UWidget* InHandle)
		: DraggableWidget(InDraggableWidget)
		, Handle(InHandle)
	{}

	bool IsValid() const
	{
		return DraggableWidget != nullptr && Handle != nullptr;
	}

	UPROPERTY()
	UUserWidget* DraggableWidget;

	UPROPERTY()
	UWidget* Handle;
};

UINTERFACE(MinimalAPI)
class UDraggableInterface : public UInterface
{
	GENERATED_BODY()
};

class UI_API IDraggableInterface
{
	GENERATED_BODY()

public:

	virtual FDraggableHandle GetDraggableHandle() = 0;
};
