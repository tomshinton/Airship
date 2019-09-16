// Airship Project - Tom Shinton 2018

#include "Runtime/UI/Public/Widgets/InspectorPanel/InspectorPanel.h"
#include "Runtime/UI/Public/Utils/HUDTools.h"

#include <AirCore/Public/Core/AirChar.h>
#include <Runtime/UMG/Public/Animation/WidgetAnimationDelegateBinding.h>
#include <Runtime/UMG/Public/Components/TextBlock.h>
#include <Runtime/UMG/Public/Animation/WidgetAnimation.h>
#include <Runtime/Utils/Public/Input/BindingFunctions.h>

namespace InspectorPanelPrivate
{
	const FName InteractBindingText("Interact");
}

UInspectorPanel::UInspectorPanel(const FObjectInitializer& ObjectInitializer)
	: UAirWidget(ObjectInitializer)
	, DisplayNameBlock(nullptr)
	, InteractionKeyBlock(nullptr)
	, ShowAnim(nullptr)
	, HideAnim(nullptr)
	, InteractionInterface(nullptr)
{}

void UInspectorPanel::NativeConstruct()
{
	Super::NativeConstruct();

	if (HideAnim)
	{
		FWidgetAnimationDynamicEvent OnHideAnimOver;
		OnHideAnimOver.BindUFunction(this, "OnHidePanelOver");

		BindToAnimationFinished(HideAnim, OnHideAnimOver);
	}
}

void UInspectorPanel::OnHidePanelOver()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UInspectorPanel::ShowPanel(const IInteractableInterface& InteractableInterface)
{
	if (DisplayNameBlock && InteractionKeyBlock)
	{
		SetVisibility(ESlateVisibility::Visible);
		DisplayNameBlock->SetText(InteractableInterface.GetDisplayName());
		InteractionKeyBlock->SetText(GetInteractionKeyString());

		PlayAnimation(ShowAnim);
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
