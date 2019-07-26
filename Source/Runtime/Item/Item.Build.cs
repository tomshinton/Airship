// Airship Project - Tom Shinton 2018

using UnrealBuildTool;

public class Item : ModuleRules
{
	public Item(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
        {
            "AirCore",
            "Core",
            "CoreUObject",
            "Engine",
            "Inventory",
            "Projectile",
            "UI"
        });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "UMG"
        });

		PublicIncludePaths.AddRange(new string[] {"Runtime/Item/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/Item/Private"});

    }
}
