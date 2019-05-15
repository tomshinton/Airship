// Copyright 2019 Tom Shinton. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class MoreManagers : ModuleRules
{
	public MoreManagers(ReadOnlyTargetRules Target) : base(Target)
	{
        PrivatePCHHeaderFile = Path.Combine(ModuleDirectory, "Public/MoreManagers.h");

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Engine" });
    }
}
