// Airship Project - Tom Shinton 2018

#include "InspectorPanel.h"
#include "TextBlock.h"
#include "Engine/Engine.h"
#include "AirWidget.h"
#include "AirChar.h"
#include "Utils/Functions/BindingFunctions.h"

namespace InspectorPanelAnims
{
	const FName Anim_Show("ShowAnim");
	const FName Anim_Hide("HideAnim");
}

namespace InspectorPanelPrivate
{
	const FName InteractBindingText("Interact");
}

UInspectorPanel::UInspectorPanel(const FObjectInitializer& ObjectInitializer)
	: UAirWidget(ObjectInitializer)
	, DisplayNameBlock(nullptr)
	, InteractionKeyBlock(nullptr)
	, InteractionInterface()
{}

void UInspectorPanel::ShowPanel(const IInteractableInterface& InteractableInterface)
{
	if (DisplayNameBlock && InteractionKeyBlock)
	{
		DisplayNameBlock->SetText(InteractableInterface.GetDisplayName());
		InteractionKeyBlock->SetText(GetInteractionKeyString());

		SetVisibility(ESlateVisibility::Visible);
		PlayAnimation(GetAnimationByName(InspectorPanelAnims::Anim_Show));
	}
}

void UInspectorPanel::HidePanel()
{
	PlayAnimation(GetAnimationByName(InspectorPanelAnims::Anim_Hide));
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
				ShowPanel(*NewInteractableInterface);
			}
			else
			{
				HidePanel();
			}
		});
	}
}

FText UInspectorPanel::GetInteractionKeyString() const
{
	if (LocalChar)
	{
		if (APlayerController* LocalController = Cast<APlayerController>(LocalChar->GetController()))
		{
			TArray<FInputActionKeyMapping> Keys;
			UBindingFunctions::GetKeysForAction(InspectorPanelPrivate::InteractBindingText, LocalController, Keys);

			if (Keys.Num() > 0)
			{
				const FString KeyString = Keys[0].Key.GetFName().ToString();
				const FString StringReadable = FString::Printf(TEXT("%s%s%s"), "[", *KeyString, "]");

				return FText::FromString(StringReadable);
			}
		}
	}

	return FText();
}
