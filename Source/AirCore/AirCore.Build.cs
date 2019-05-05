// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class AirCore : ModuleRules
{
	public AirCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

		PublicIncludePaths.AddRange(new string[] {"AirCore/Public"});
		PrivateIncludePaths.AddRange(new string[] {"AirCore/Private"});
	}
}
