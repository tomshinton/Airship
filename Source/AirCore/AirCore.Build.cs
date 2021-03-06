// Airship Project - Tom Shinton 2018

using UnrealBuildTool;

public class AirCore : ModuleRules
{
	public AirCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "UMG"
        });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "UI",
            "Utils"
        });

        PublicDependencyModuleNames.AddRange(new string[] { "MoreManagers" });

        PublicIncludePaths.AddRange(new string[] {"AirCore/Public"});
		PrivateIncludePaths.AddRange(new string[] {"AirCore/Private"});
	}
}
