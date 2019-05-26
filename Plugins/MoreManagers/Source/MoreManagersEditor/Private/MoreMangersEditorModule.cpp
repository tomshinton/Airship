// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagersEditorModule.h"

#include <MoreManagers/Public/ManagerCore/InvokeList.h>

#include <Developer/AssetTools/Public/AssetToolsModule.h>
#include <Developer/Settings/Private/SettingsContainer.h>
#include <Developer/Settings/Public/ISettingsModule.h>
#include <Developer/Settings/Public/ISettingsSection.h>
#include <Runtime/Core/Public/Internationalization/Internationalization.h>
#include <Runtime/Projects/Public/Interfaces/IPluginManager.h>
#include <Runtime/SlateCore/Public/Brushes/SlateImageBrush.h>

IMPLEMENT_MODULE(FMoreManagersEditorModule, MoreManagersEditor);
DEFINE_LOG_CATEGORY(MoreManagersEditorLog)

#define LOCTEXT_NAMESPACE "MoreManagers"

void FMoreManagersEditorModule::StartupModule()
{
	UE_LOG(MoreManagersEditorLog, Log, TEXT("MoreManagersEditorLog: Module Started"));
	
	RegisterAssetCategory();
	SetModuleIcon();
	RegisterUnmutableSettings();
}

void FMoreManagersEditorModule::ShutdownModule()
{
	UE_LOG(MoreManagersEditorLog, Warning, TEXT("MoreManagersEditorLog: Module Shutdown"));
}

void FMoreManagersEditorModule::RegisterAssetCategory()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	MoreManagerCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("MoreManagers")), LOCTEXT("MoreManagersCategoryName", "More Managers"));
}

void FMoreManagersEditorModule::SetModuleIcon()
{
	StyleSet = MakeShareable(new FSlateStyleSet("MoreManagersStyle"));
	const FString ContentDir = IPluginManager::Get().FindPlugin("MoreManagers")->GetBaseDir();
	StyleSet->SetContentRoot(ContentDir);

	FSlateImageBrush* ThumbnailBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Resources/ManagerIcon128"), TEXT(".png")), FVector2D(128.f, 128.f));

	if (ThumbnailBrush)
	{
		StyleSet->Set("ClassThumbnail.Manager", ThumbnailBrush);
		FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
	}
}

void FMoreManagersEditorModule::RegisterUnmutableSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");
		ISettingsSectionPtr InvokeListSection = SettingsModule->RegisterSettings("Project", "MoreManagers", "Invoke",
			LOCTEXT("MoreManagersSettings", "Invoke List"),
			LOCTEXT("MoreManagersSettingsDescription", "MoreManagers Invoke List - What classes do we need to spin up, and in what order?"),
			GetMutableDefault<UInvokeList>());

		if (InvokeListSection.IsValid())
		{
			InvokeListSection->OnModified().BindRaw(this, &FMoreManagersEditorModule::HandleSaved);
		}
	}
}

void FMoreManagersEditorModule::UnregisterUnmutableSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Colony Settings", "AI");
	}
}

bool FMoreManagersEditorModule::HandleSaved()
{
	UInvokeList* InvokeList = GetMutableDefault<UInvokeList>();
	InvokeList->SaveConfig();

	return true;
}

#undef LOCTEXT_NAMESPACE