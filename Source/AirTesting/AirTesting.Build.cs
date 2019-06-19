// Editor only testing module

using UnrealBuildTool;

public class AirTesting : ModuleRules
{
	public AirTesting(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicIncludePaths.AddRange(new string[] { "AirTesting/Public" });
		
        PrivateIncludePaths.AddRange(new string[] { "AirTesting/Private" });

        PublicDependencyModuleNames.AddRange(new string[] { "Airship", "AirCore", "Core", "CoreUObject", "Engine", "EditorTests", "InputCore", "UnrealEd" });
    }
};
