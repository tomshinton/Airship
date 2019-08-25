// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/Actions/DraggableAction.h"

#include <Runtime/UMG/Public/Blueprint/UserWidget.h>
#include <Runtime/Engine/Classes/Components/InputComponent.h>

DEFINE_LOG_CATEGORY(DraggableActionLog);

FDraggableAction::FDraggableAction(UUserWidget& InParent)
	: ParentWidget(&InParent)
{}

void FDraggableAction::Init(UInputComponent& InInputComponent)
{
#if !UE_BUILD_SHIPPING
	UE_LOG(DraggableActionLog, Log, TEXT("Binding %s for draggable actions"), *ParentWidget->GetName());
#endif //!UE_BUILD_SHIPPING

	FInputActionBinding StartDragAction("DragUIElement", IE_Pressed);
	StartDragAction.ActionDelegate.GetDelegateForManualSet().BindRaw(this, &FDraggableAction::StartDrag);
	InInputComponent.AddActionBinding(StartDragAction);

	FInputActionBinding EndDragAction("DragUIElement", IE_Released);
	EndDragAction.ActionDelegate.GetDelegateForManualSet().BindRaw(this, &FDraggableAction::EndDrag);
	InInputComponent.AddActionBinding(EndDragAction);
}

void FDraggableAction::StartDrag()
{

}

void FDraggableAction::EndDrag()
{

}
