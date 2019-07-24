// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class AirEditor : ModuleRules
{
	public AirEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "Editor/AirEditor/Public" });

        PrivateIncludePaths.AddRange(new string[] { "Editor/AirEditor/Private" });

        PublicDependencyModuleNames.AddRange(new string[] { "AirCore", "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
};
