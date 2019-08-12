// Copyright 2019 Tom Shinton. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class MoreManagersEditor : ModuleRules
{
	public MoreManagersEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = Path.Combine(ModuleDirectory, "Public/MoreManagersEditorModule.h");

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "AssetRegistry",
            "Core",
            "CoreUObject",
            "ContentBrowser",
            "BlueprintGraph",
            "EditorStyle",
            "EditorWidgets",
            "Engine",
            "InputCore",
            "Json",
            "KismetWidgets",
            "Kismet",
            "MoreManagers",
            "PropertyEditor",
            "Projects",
            "RenderCore",
            "Slate",
            "SlateCore",
            "UnrealEd",
            "WorkspaceMenuStructure",
        });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "MoreManagers",
            "EditorStyle",
            "LevelEditor"
        });

        DynamicallyLoadedModuleNames.AddRange(new string[]
        {
            "AssetTools"
        });
    }
};
