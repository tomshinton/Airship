// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include "MoreManagersEditor/Public/MoreManagersEditorInterface.h"
#include "Modules/ModuleManager.h"

#include <Developer/AssetTools/Public/AssetTypeCategories.h>
#include <Developer/AssetTools/Public/IAssetTools.h>
#include <Developer/AssetTools/Public/IAssetTypeActions.h>
#include <Editor/UnrealEd/Public/UnrealEd.h>

DECLARE_LOG_CATEGORY_EXTERN(MoreManagersEditorLog, All, All)

extern const FName ManagerEditorAppIdentifier;

class FMoreManagersEditorModule : public IMoreManagersEditorInterface
{

public:

	TSharedPtr<FSlateStyleSet> StyleSet;

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	EAssetTypeCategories::Type GetMoreManagerCategoryBit() { return MoreManagerCategoryBit; };

	//IMoreManagersEditorInterface
	virtual TSharedRef<IManagerEditor> CreateManagerEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UManager* InManager) override;
	virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override;
	virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override;
	//~IMoreManagersEditorInterface

private:

	EAssetTypeCategories::Type MoreManagerCategoryBit;

	void RegisterAssetCategory(IAssetTools& AssetTools);
	void SetModuleIcon();

	void RegisterUnmutableSettings();
	void UnregisterUnmutableSettings();

	bool HandleSaved();

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;
	TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;
};