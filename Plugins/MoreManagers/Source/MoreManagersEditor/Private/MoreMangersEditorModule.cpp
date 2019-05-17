// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagersEditorModule.h"

#include <Developer/AssetTools/Public/AssetToolsModule.h>
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

#undef LOCTEXT_NAMESPACE