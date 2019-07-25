// Airship Project - Tom Shinton 2018

using UnrealBuildTool;

public class UI : ModuleRules
{
	public UI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "Inventory",
            "Slate",
            "SlateCore",
            "UMG"
        });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "Slate",
            "SlateCore"
        });

		PublicIncludePaths.AddRange(new string[] {"Runtime/UI/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/UI/Private"});
    }
}
