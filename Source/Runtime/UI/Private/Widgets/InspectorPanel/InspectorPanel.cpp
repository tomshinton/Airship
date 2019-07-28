// Airship Project - Tom Shinton 2018

#include "InspectorPanel.h"
#include "TextBlock.h"
#include "Engine/Engine.h"
#include "AirWidget.h"
#include "AirChar.h"
#include "Utils/Functions/BindingFunctions.h"
#include "HUDTools.h"

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
		if (UHUDTools::IsVisible(*this))
		{
			DisplayNameBlock->SetText(InteractableInterface.GetDisplayName());
			InteractionKeyBlock->SetText(GetInteractionKeyString());

			PlayAnimation(ShowAnim);
		}
	}
}

void UInspectorPanel::HidePanel()
{
	PlayAnimation(HideAnim);
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
