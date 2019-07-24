// Airship Project - Tom Shinton 2018

using UnrealBuildTool;

public class Wielding : ModuleRules
{
	public Wielding(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

		PublicIncludePaths.AddRange(new string[] {"Runtime/Wielding/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/Wielding/Private"});

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
