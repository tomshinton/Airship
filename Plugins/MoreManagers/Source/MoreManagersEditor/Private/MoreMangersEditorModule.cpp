// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagersEditorModule.h"

#include "MoreManagersEditor/Public/InvokeTool/InvokeToolCommands.h"
#include "MoreManagersEditor/Public/InvokeTool/InvokeToolCustomization.h"

#include <Developer/AssetTools/Public/AssetToolsModule.h>
#include <Editor/LevelEditor/Public/LevelEditor.h>
#include <Editor/PropertyEditor/Public/PropertyEditorDelegates.h>
#include <Editor/PropertyEditor/Public/PropertyEditorModule.h>
#include <Runtime/Core/Public/Internationalization/Internationalization.h>
#include <Runtime/Projects/Public/Interfaces/IPluginManager.h>
#include <Runtime/Slate/Public/Framework/Commands/UIAction.h>
#include <Runtime/Slate/Public/Framework/MultiBox/MultiBoxExtender.h>
#include <Runtime/SlateCore/Public/Brushes/SlateImageBrush.h>

IMPLEMENT_MODULE(FMoreManagersEditorModule, MoreManagersEditor);

DEFINE_LOG_CATEGORY(MoreManagersEditorLog)
DEFINE_LOG_CATEGORY(InvokeToolLog)

namespace ToolbarExtensionNames
{
	const FName InvokeToolHook = TEXT("Game");
}

#define LOCTEXT_NAMESPACE "MoreManagers"

void FMoreManagersEditorModule::StartupModule()
{
	UE_LOG(MoreManagersEditorLog, Log, TEXT("MoreManagersEditorLog: Module Started"));
	
	RegisterAssetCategory();
	SetModuleIcon();

	RegisterInvokeTool();
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

void FMoreManagersEditorModule::RegisterInvokeTool()
{
	//Register InvokeTool Customization
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout("InvokeTool", FOnGetDetailCustomizationInstance::CreateStatic(&FInvokeToolCustomization::MakeInstance));

	PropertyModule.NotifyCustomizationModuleChanged();

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	FInvokeToolCommands::Register();
	TSharedPtr<FUICommandList> CommandList = MakeShareable(new FUICommandList);

	CommandList->MapAction(FInvokeToolCommands::Get().ShowInvokeTool, FExecuteAction::CreateRaw(this, &FMoreManagersEditorModule::ShowInvokeTool));
	
	struct Tools
	{
		static void AddMenuCommands(FToolBarBuilder& ToolbarBuilder)
		{
			ToolbarBuilder.AddToolBarButton(FInvokeToolCommands::Get().ShowInvokeTool);
		}
	};

	TSharedRef<FExtender> ToolbarExtender(new FExtender());
	ToolbarExtender->AddToolBarExtension(ToolbarExtensionNames::InvokeToolHook, EExtensionHook::Before, CommandList.ToSharedRef(), FToolBarExtensionDelegate::CreateStatic(&Tools::AddMenuCommands));
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}

void FMoreManagersEditorModule::ShowInvokeTool()
{
	UE_LOG(InvokeToolLog, Log, TEXT("InvokeTool: Summoning Tool"));

	UInvokeTool* ToolInstance = NewObject<UInvokeTool>(GetTransientPackage());
	ToolInstance->AddToRoot();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	TArray<UObject*> ObjectsToView;
	ObjectsToView.Add(ToolInstance);

	TSharedRef<SWindow> Window = SNew(SWindow)
		.Title(LOCTEXT("InvokeTool", "MoreManagers Invoke Tool"))
		.ClientSize(FVector2D(400, 400));

	GEditor->EditorAddModalWindow(Window);

	Window->SetOnWindowClosed(FOnWindowClosed::CreateLambda([ToolInstance](const TSharedRef<SWindow>& Window)
	{
		ToolInstance->RemoveFromRoot();
	}));
}

#undef LOCTEXT_NAMESPACE