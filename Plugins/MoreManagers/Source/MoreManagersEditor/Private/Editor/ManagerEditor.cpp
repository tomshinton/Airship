// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include "MoreManagersEditor/Public/Editor/ManagerEditor.h"
#include "MoreManagersEditor/Public/Editor/ManagerEditorSchema.h"
#include "MoreManagersEditor/Public/MoreManagersEditorModule.h"

#include <Editor/EditorStyle/Public/EditorStyleSet.h>
#include <Editor/PropertyEditor/Public/PropertyEditorModule.h>
#include <Editor/PropertyEditor/Public/IDetailsView.h>
#include <Editor/UnrealEd/Public/Editor.h>
#include <Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h>
#include <Runtime/Core/Public/Modules/ModuleManager.h>
#include <Runtime/Slate/Public/Framework/Docking/TabManager.h>
#include <Runtime/Slate/Public/Widgets/Docking/SDockTab.h>
#include <Runtime/SlateCore/Public/Widgets/SOverlay.h>
#include <UnrealEd/Public/Toolkits/AssetEditorToolkit.h>
#include <UnrealEd/Public/GraphEditor.h>

#define LOCTEXT_NAMESPACE "ManagerEditor"

const FName FManagerEditor::ToolkitFName(TEXT("ManagerEditor"));
const FName FManagerEditor::PropertiesTabID(TEXT("ManagerEditor_Properties"));
const FName FManagerEditor::GraphTabID(TEXT("ManagerEditor_Graph"));

void FManagerEditor::InitManagerEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UManager* InManager)
{
	const bool IsUpdatable = false;
	const bool AllowFavourites = true;
	const bool IsLockable = false;

	SetManager(InManager);

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs(IsUpdatable, IsLockable, true, FDetailsViewArgs::ObjectsUseNameArea, false);

	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_ManagerEditor_Layout")->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.1f)
			->SetHideTabWell(true)
			->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
		)
		->Split
		(
			FTabManager::NewSplitter()
			->Split
			(
				FTabManager::NewStack()
				->AddTab(GraphTabID, ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(PropertiesTabID, ETabState::OpenedTab)
			)
		)
	);

	const bool CreateDefaultStandaloneMenu = true;
	const bool CreateDefaultToolbar = true;

	FAssetEditorToolkit::InitAssetEditor(
		Mode, 
		InitToolkitHost, 
		ManagerEditorAppIdentifier,
		StandaloneDefaultLayout,
		CreateDefaultStandaloneMenu,
		CreateDefaultToolbar,
		(UObject*)(InManager)
	);

	if (DetailsView.IsValid())
	{
		DetailsView->SetObject((UObject*)InManager);
	}

	Graph = CreateManagerGraph();
}

void FManagerEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_ManagerEditor", "Manager Editor"));

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(PropertiesTabID, FOnSpawnTab::CreateSP
	(this, &FManagerEditor::SpawnPropertiesTab))
		.SetDisplayName(LOCTEXT("PropertiesTab", "Details"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner(GraphTabID, FOnSpawnTab::CreateSP
	(this, &FManagerEditor::SpawnGraphTab))
		.SetDisplayName(LOCTEXT("GraphTab", "Manager Logic"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));
}

void FManagerEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}

UEdGraph* FManagerEditor::GetGraph()
{
	UEdGraph* NewGraph = FBlueprintEditorUtils::CreateNewGraph((UObject*)Manager, NAME_None, UEdGraph::StaticClass(), UManagerEditorSchema::StaticClass());
	NewGraph->bAllowDeletion = false;

	// Give the schema a chance to fill out any required nodes (like the results node)
	const UEdGraphSchema* Schema = NewGraph->GetSchema();
	Schema->CreateDefaultNodesForGraph(*NewGraph);

	return NewGraph;
}

TSharedRef<SGraphEditor> FManagerEditor::CreateManagerGraph()
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("ManagerEditor_CornerText", "Manager");

	return SNew(SGraphEditor)
		//.AdditionalCommands(GraphEditorCommands)
		.IsEditable(true)
		.Appearance(AppearanceInfo)
		.GraphToEdit(GetGraph())
		//.GraphEvents(InEvents)
		.AutoExpandActionMenu(true)
		.ShowGraphStateOverlay(false);
}

TSharedRef<SDockTab> FManagerEditor::SpawnPropertiesTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("GenericEditor.Tabs.Properties"))
		.Label(LOCTEXT("GenericDetailsTitle", "Details"))
		.ShouldAutosize(true)
		.TabColorScale(GetTabColorScale())
		[
			DetailsView.ToSharedRef()
		];
}

TSharedRef<SDockTab> FManagerEditor::SpawnGraphTab(const FSpawnTabArgs& Args)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.Label(LOCTEXT("ManagerEditorTabTitle", "Manager Logic"));

	if (Graph.IsValid())
	{
		SpawnedTab->SetContent(Graph.ToSharedRef());
	}

	return SpawnedTab;
}

#undef LOCTEXT_NAMESPACE