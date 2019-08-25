// Airship Project - Tom Shinton 2018

#pragma once

class UUserWidget;

class FDraggableAction
{
public:

	FDraggableAction(UUserWidget& InParent);

private:

	UPROPERTY()
	UUserWidget* ParentWidget;
};