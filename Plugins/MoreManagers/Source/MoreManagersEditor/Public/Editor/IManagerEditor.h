// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include "Editor/UnrealEd/Public/Toolkits/AssetEditorToolkit.h"

class UManager;

class IManagerEditor : public FAssetEditorToolkit
{
public:

	virtual UManager* GetManager() const = 0;
	virtual void SetManager(UManager* InManager) = 0;
};