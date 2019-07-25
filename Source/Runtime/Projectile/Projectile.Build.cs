// Airship Project - Tom Shinton 2018

using UnrealBuildTool;

public class Projectile : ModuleRules
{
	public Projectile(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
        {
            "Core",
            "Item" 
        });

		PublicIncludePaths.AddRange(new string[] {"Runtime/Projectile/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/Projectile/Private"});

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
