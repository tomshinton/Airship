// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include <Runtime/Core/Public/Modules/ModuleInterface.h>
#include <Editor/UnrealEd/Public/Toolkits/IToolkitHost.h>
#include <Editor/UnrealEd/Public/Toolkits/AssetEditorToolkit.h>

class IManagerEditor;
class UManager;

class IMoreManagersEditorInterface : public IModuleInterface
	, public IHasMenuExtensibility
	, public IHasToolBarExtensibility
{

public:

	virtual TSharedRef<IManagerEditor> CreateManagerEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UManager* CustomAsset) = 0;
};