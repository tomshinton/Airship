// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UI/Public/Actions/DraggableAction.h"

#include <Runtime/Engine/Classes/Components/InputComponent.h>
#include <Runtime/UMG/Public/Blueprint/UserWidget.h>
#include <Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h>
#include <Runtime/UMG/Public/Blueprint/WidgetTree.h>
#include <Runtime/UMG/Public/Components/CanvasPanelSlot.h>

DEFINE_LOG_CATEGORY(DraggableActionLog);

FDraggableAction::FDraggableAction(UUserWidget& InParent)
	: TargetWidget(&InParent)
	, TargetTree(nullptr)
	, CachedWorld(nullptr)
	, CachedPlayerController(nullptr)
	, DraggableHandle()
	, MoveTimerHandle()
	, MoveTimerDelegate()
	, MoveRate(1.f/60.f) //About 60 times a second
	, NonmoveRate(1.f/10.f) //About 10 times a second
	, IsDragging(false)
	, InitialMouseOffset()
{
	MoveTimerDelegate.BindRaw(this, &FDraggableAction::DoMove);
}

void FDraggableAction::Init(UInputComponent& InInputComponent)
{
	if (TargetWidget)
	{
		TargetTree = TargetWidget->WidgetTree;

		if (!TargetTree)
		{
			UE_LOG(DraggableActionLog, Error, TEXT("Could not get valid WidgetTree from %s - Draggable Actions are disabled.  Returning"), *TargetWidget->GetName());
			return;
		}

#if !UE_BUILD_SHIPPING
		UE_LOG(DraggableActionLog, Log, TEXT("Binding %s for draggable actions"), *TargetWidget->GetName());
#endif //!UE_BUILD_SHIPPING

		FInputActionBinding StartDragAction("DragUIElement", IE_Pressed);
		StartDragAction.ActionDelegate.GetDelegateForManualSet().BindRaw(this, &FDraggableAction::StartDrag);
		InInputComponent.AddActionBinding(StartDragAction);

		FInputActionBinding EndDragAction("DragUIElement", IE_Released);
		EndDragAction.ActionDelegate.GetDelegateForManualSet().BindRaw(this, &FDraggableAction::EndDrag);
		InInputComponent.AddActionBinding(EndDragAction);

		if (UWorld* World = InInputComponent.GetWorld()) 
		{
			CachedWorld = World;
		}

		SetTimerRate(NonmoveRate);
	}
}

void FDraggableAction::StartDrag()
{
	if (DraggableHandle.IsSet() && !IsDragging)
	{
		IsDragging = true;

		SetTimerRate(MoveRate);
	}
}

void FDraggableAction::EndDrag()
{
	if (DraggableHandle.IsSet())
	{
		IsDragging = false;
		DraggableHandle.Reset();

		SetTimerRate(NonmoveRate);
	}
}

void FDraggableAction::DoMove()
{
	if (TargetTree)
	{
		if (!IsDragging)
		{
			TArray < UWidget*> Widgets;
			TargetTree->GetChildWidgets(TargetTree->RootWidget, Widgets);

			for (UWidget* Widget : Widgets)
			{
				if (IDraggableInterface* DraggableInterface = Cast<IDraggableInterface>(Widget))
				{
					const FDraggableHandle ElectedHandle = DraggableInterface->GetDraggableHandle();
					if (ElectedHandle.IsValid())
					{
						if (ElectedHandle.Handle->IsHovered())
						{
							SetupDrag(ElectedHandle);
							return;
						}
					}
				}
			}

			DraggableHandle.Reset();
		}

		if (DraggableHandle.IsSet() && IsDragging)
		{
			if (UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(DraggableHandle->DraggableWidget))
			{
				float MouseX = 0.f;
				float MouseY = 0.f;

				UWidgetLayoutLibrary::GetMousePositionScaledByDPI(CachedPlayerController, MouseX, MouseY);

				const FVector2D NewPosition = FVector2D(MouseX, MouseY) + InitialMouseOffset;

				CanvasSlot->SetPosition(NewPosition);
			}
			else
			{
				UE_LOG(DraggableActionLog, Warning, TEXT("Cached moving widget cannot be cast to UCanvasPanel slot in FDraggableAction::DoMove - panel will not move"));
			}
		}
	}
}

void FDraggableAction::SetupDrag(const FDraggableHandle& InDraggableHandle)
{
#if !UE_BUILD_SHIPPING
	check(CachedPlayerController);
#endif //!UE_BUILD_SHIPPING

	if (UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InDraggableHandle.DraggableWidget))
	{
		DraggableHandle = InDraggableHandle;

		float MouseX = 0.f;
		float MouseY = 0.f;

		const FVector2D IntialLocation = CanvasSlot->GetPosition();
		UWidgetLayoutLibrary::GetMousePositionScaledByDPI(CachedPlayerController, MouseX, MouseY);
		InitialMouseOffset = IntialLocation - FVector2D(MouseX, MouseY);
	}
}

void FDraggableAction::SetTimerRate(const float InNewRate)
{
#if !UE_BUILD_SHIPPING
	check(CachedWorld);
#endif //!UE_BUILD_SHIPPING

	UE_LOG(DraggableActionLog, Log, TEXT("Setting new Draggable Update Frequency to %f"), InNewRate);

	CachedWorld->GetTimerManager().SetTimer(MoveTimerHandle, MoveTimerDelegate, InNewRate, true, InNewRate);
	CachedPlayerController = CachedWorld->GetFirstPlayerController();
}
