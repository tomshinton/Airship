// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class AirEditor : ModuleRules
{
	public AirEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;


        PublicDependencyModuleNames.AddRange(new string[] 
        {
            "AirCore",
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "Input",
            "Inventory",
            "UI"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[] { "Editor/AirEditor/Public" });
        PrivateIncludePaths.AddRange(new string[] { "Editor/AirEditor/Private" });
    }
};
