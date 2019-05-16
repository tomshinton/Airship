// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagersEditorModule.h"

#include <Developer/AssetTools/Public/AssetToolsModule.h>
#include <Runtime/Core/Public/Internationalization/Internationalization.h>

IMPLEMENT_MODULE(FMoreManagersEditorModule, MoreManagersEditor);
DEFINE_LOG_CATEGORY(MoreManagersEditorLog)

#define LOCTEXT_NAMESPACE "MoreManagers"

void FMoreManagersEditorModule::StartupModule()
{
	UE_LOG(MoreManagersEditorLog, Log, TEXT("MoreManagersEditorLog: Module Started"));
	
	RegisterAssetCategory();
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

#undef LOCTEXT_NAMESPACE