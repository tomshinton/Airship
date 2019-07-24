// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class AirUI : ModuleRules
{
	public AirUI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "Inventory",
            "UMG"
        });

		PublicIncludePaths.AddRange(new string[] {"Runtime/AirUI/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/AirUI/Private"});

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
