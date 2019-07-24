// Airship Project - Tom Shinton 2018

using UnrealBuildTool;

public class EmptyModule : ModuleRules
{
	public EmptyModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

		PublicIncludePaths.AddRange(new string[] {"Runtime/EmptyModule/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/EmptyModule/Private"});

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
