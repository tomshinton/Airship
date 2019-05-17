// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

#include <Developer/AssetTools/Public/AssetTypeCategories.h>
#include <Editor/UnrealEd/Public/UnrealEd.h>

DECLARE_LOG_CATEGORY_EXTERN(MoreManagersEditorLog, All, All)

class FMoreManagersEditorModule : public IModuleInterface
{

public:

	TSharedPtr<FSlateStyleSet> StyleSet;

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	EAssetTypeCategories::Type GetMoreManagerCategoryBit() { return MoreManagerCategoryBit; };

private:

	EAssetTypeCategories::Type MoreManagerCategoryBit;

	void RegisterAssetCategory();
	void SetModuleIcon();
};
