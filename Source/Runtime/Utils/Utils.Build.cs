// Airship Project - Tom Shinton 2018

using UnrealBuildTool;

public class Utils : ModuleRules
{
	public Utils(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore"
        });

        PrivateDependencyModuleNames.AddRange(new string[]{});

		PublicIncludePaths.AddRange(new string[] {"Runtime/Utils/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/Utils/Private"});
    }
}
