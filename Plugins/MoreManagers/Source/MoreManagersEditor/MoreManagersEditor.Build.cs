// Fill out your copyright notice in the Description page of Project Settings.

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
            "AssetTools",
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "MainFrame",
            "MoreManagers",
            "Projects",
            "PropertyEditor",
            "Slate",
            "SlateCore",
            "UnrealEd"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { "MoreManagers" });
    }
};
