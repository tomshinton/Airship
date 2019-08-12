// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include "MoreManagersEditor/Public/Editor/IManagerEditor.h"

#include <Editor/UnrealEd/Public/Toolkits/IToolkitHost.h>
#include <Editor/UnrealEd/Public/Toolkits/AssetEditorToolkit.h>
#include <Editor/PropertyEditor/Public/PropertyEditorDelegates.h>
#include <Runtime/Core/Public/Internationalization/Internationalization.h>


class IDetailsView;
class SDockableTab;
class UManager;

class MOREMANAGERSEDITOR_API FManagerEditor : public IManagerEditor
{

public:

	void InitManagerEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UManager* InManager);

	//FAssetEditorToolkit
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager);
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager);
	//~FAssetEditorToolkit

	//IToolkitInterface
	virtual FName GetToolkitFName() const override { return ToolkitFName; };
	virtual FText GetBaseToolkitName() const override { return NSLOCTEXT("ManagerEditor", "AppLabel", "ManagerEditor"); };
	virtual FText GetToolkitName() const override { return FText::FromName(ToolkitFName); };
	virtual FText GetToolkitToolTipText() const override { return NSLOCTEXT("ManagerEditor", "Tooltip", "Manager Editor"); };
	virtual FString GetWorldCentricTabPrefix() const override { return NSLOCTEXT("ManagerEditor", "WorldCentricTabPrefix", "AnimationDatabase ").ToString(); };
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FColor::Red; };
	virtual bool IsPrimaryEditor() const override { return true; };
	//~IToolkitInterface

	//IManagerEditorInterface
	virtual UManager* GetManager() const override { return Manager; };
	virtual void SetManager(UManager* InManager) override { Manager = InManager; };
	//~IManagerEditorInterface

private:

	static const FName ToolkitFName;
	static const FName PropertiesTabID;
	static const FName GraphTabID;

	UEdGraph* GetGraph();

	TSharedPtr<SGraphEditor> Graph;
	TSharedRef<SGraphEditor> CreateManagerGraph();
	TSharedRef<SDockTab> SpawnPropertiesTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnGraphTab(const FSpawnTabArgs& Args);

	TSharedPtr<SDockTab> PropertiesTab;
	TSharedPtr<SGraphEditor> ManagerGraph;
	TSharedPtr<IDetailsView> DetailsView;

	UPROPERTY()
	UManager* Manager;
};