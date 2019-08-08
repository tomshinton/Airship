// Airship Project - Tom Shinton 2018

using UnrealBuildTool;

public class Input : ModuleRules
{
	public Input(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
        {
            "Core",
            "CoreUObject",
            "Engine"
        });

		PublicIncludePaths.AddRange(new string[] {"Runtime/Input/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/Input/Private"});

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
