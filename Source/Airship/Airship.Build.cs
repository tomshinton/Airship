// Airship Project - Tom Shinton 2018

using UnrealBuildTool;

public class Airship : ModuleRules
{
	public Airship(ReadOnlyTargetRules Target) : base(Target)
	{
       PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
