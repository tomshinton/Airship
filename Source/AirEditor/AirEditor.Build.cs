// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class AirEditor : ModuleRules
{
	public AirEditor(ReadOnlyTargetRules Target) : base(Target)
    { 
        PublicIncludePaths.AddRange(new string[] { "AirEditor/Public" });

        PrivateIncludePaths.AddRange(new string[] { "AirEditor/Private" });

        PublicDependencyModuleNames.AddRange(new string[] { "Airship", "AirCore", "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
};
