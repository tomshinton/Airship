// Airship Project - Tom Shinton 2018

using UnrealBuildTool;

public class UI : ModuleRules
{
	public UI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {   
        });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "AirCore",
            "Core",
            "CoreUObject",
            "Engine",
            "Input",
            "InputCore",
            "Inventory",
            "Slate",
            "SlateCore",
            "UMG",
            "Slate",
            "SlateCore",
            "Utils"
        });

		PublicIncludePaths.AddRange(new string[] {"Runtime/UI/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/UI/Private"});
    }
}
