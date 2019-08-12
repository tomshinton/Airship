// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include "MoreManagersEditor/Public/Actions/AssetTypeActions_Manager.h"
#include "MoreManagersEditor/Public/MoreManagersEditorModule.h"

#include <MoreManagers/Public/ManagerCore/Manager.h>
#include <Editor/EditorStyle/Public/EditorStyleSet.h>
#include <Runtime/Core/Public/Internationalization/Internationalization.h>
#include <Runtime/SlateCore/Public/Textures/SlateIcon.h>
#include "SNotificationList.h"
#include "NotificationManager.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_Manager"

FAssetTypeActions_Manager::FAssetTypeActions_Manager()
{
}

void FAssetTypeActions_Manager::GetActions(const TArray<UObject*>& InObjects, class FMenuBuilder& MenuBuilder)
{
	if (InObjects.Num() > 0)
	{
		MenuBuilder.AddMenuEntry(
		LOCTEXT("Manager_AddToInvokeList", "Add Manager to Invoke List"),
		LOCTEXT("Blueprint_AddToInvokeListTooltip", "Add this Manager to the list of Managers that get span up at runtime"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Kismet.Tabs.BlueprintDefaults"),
		FUIAction
		(
			FExecuteAction::CreateSP(this, &FAssetTypeActions_Manager::TryAddToInvokeList, InObjects[0]),
			FCanExecuteAction()
		));
	}
}

FColor FAssetTypeActions_Manager::GetTypeColor() const
{
	return FColor::Silver;
}

FText FAssetTypeActions_Manager::GetName() const
{
	return NSLOCTEXT("AssetTypeActions_Manager", "AssetTypeActions_Manager", "Manager");
}

UClass* FAssetTypeActions_Manager::GetSupportedClass() const
{
	return UManager::StaticClass();
}

uint32 FAssetTypeActions_Manager::GetCategories()
{
	FMoreManagersEditorModule& MoreManagersEditorModule = FModuleManager::LoadModuleChecked<FMoreManagersEditorModule>("MoreManagersEditor");
	return MoreManagersEditorModule.GetMoreManagerCategoryBit();
}

void FAssetTypeActions_Manager::OpenAssetEditor(const TArray<UObject *>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsUnique() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjItr = InObjects.CreateConstIterator(); ObjItr; ++ObjItr)
	{
		auto Manager = Cast<UManager>(*ObjItr);

		if (Manager)
		{
			IMoreManagersEditorInterface* EditorModuleInterface = &FModuleManager::LoadModuleChecked<FMoreManagersEditorModule>("MoreManagersEditor");
			EditorModuleInterface->CreateManagerEditor(Mode, EditWithinLevelEditor, Manager);
		}
	}
}

void FAssetTypeActions_Manager::TryAddToInvokeList(UObject* InObject)
{
	FNotificationInfo Info(LOCTEXT("ManagerAddedToList", "Manager added to Invoke List!"));
	Info.Image = FEditorStyle::GetBrush(TEXT("LevelEditor.RecompileGameCode"));
	Info.FadeInDuration = 0.1f;
	Info.FadeOutDuration = 0.5f;
	Info.ExpireDuration = 1.5f;
	Info.bUseThrobber = false;
	Info.bUseSuccessFailIcons = true;
	Info.bUseLargeFont = true;
	Info.bFireAndForget = false;
	Info.bAllowThrottleWhenFrameRateIsLow = false;
	auto NotificationItem = FSlateNotificationManager::Get().AddNotification(Info);
	NotificationItem->SetCompletionState(SNotificationItem::CS_Success);
	NotificationItem->ExpireAndFadeout();
}


#undef LOCTEXT_NAMESPACE