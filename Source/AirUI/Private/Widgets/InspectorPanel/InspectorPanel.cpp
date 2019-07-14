// Airship Project - Tom Shinton 2018

#include "InspectorPanel.h"
#include "TextBlock.h"
#include "Engine/Engine.h"

namespace InspectorPanelAnims
{
	const FName Anim_Show("ShowAnim");
	const FName Anim_Hide("HideAnim");
}

UInspectorPanel::UInspectorPanel(const FObjectInitializer& ObjectInitializer)
	: UAirWidget(ObjectInitializer)
	, DisplayNameBlock(nullptr)
	, InteractionInterface()
{}

void UInspectorPanel::OnNewItemLookedAt(const FText& InItemDisplayName)
{
	if (DisplayNameBlock)
	{
		DisplayNameBlock->SetText(InItemDisplayName);
	}
}

void UInspectorPanel::ShowPanel()
{
	SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(GetAnimationByName(InspectorPanelAnims::Anim_Show));
}

void UInspectorPanel::HidePanel()
{
	PlayAnimation(GetAnimationByName(InspectorPanelAnims::Anim_Hide));
}

void UInspectorPanel::NativeDestruct()
{
	UE_LOG(LogTemp, Log, TEXT("Inspector descroyed"));

	Super::NativeDestruct();
}

void UInspectorPanel::SetInteractionInterface(IInteractionInterface* InInteractionInterface)
{
	if (InInteractionInterface)
	{
		InteractionInterface.SetObject(this);
		InteractionInterface.SetInterface(InInteractionInterface);

		InteractionInterface->GetOnNewItemHoveredDelegate().AddLambda([this](IInteractableInterface* NewInteractableInterface)
		{
			if (NewInteractableInterface)
			{
				ShowPanel();
				OnNewItemLookedAt(NewInteractableInterface->GetDisplayName());
			}
			else
			{
				HidePanel();
			}
		});
	}
}
