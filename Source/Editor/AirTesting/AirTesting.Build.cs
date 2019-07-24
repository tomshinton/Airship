// Editor only testing module

using UnrealBuildTool;

public class AirTesting : ModuleRules
{
	public AirTesting(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "Editor/AirTesting/Public" });
		
        PrivateIncludePaths.AddRange(new string[] { "Editor/AirTesting/Private" });

        PublicDependencyModuleNames.AddRange(new string[] {"AirCore", "Core", "CoreUObject", "Engine", "EditorTests", "InputCore", "UnrealEd" });
    }
};
