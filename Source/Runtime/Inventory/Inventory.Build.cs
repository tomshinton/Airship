// Airship Project - Tom Shinton 2018

using UnrealBuildTool;

public class Inventory : ModuleRules
{
	public Inventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
        {
            "Core",
            "CoreUObject",
            "Engine",
            "Item",
            "Projectile"
        });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "Inventory"
        });

		PublicIncludePaths.AddRange(new string[] {"Runtime/Inventory/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/Inventory/Private"});

    }
}
