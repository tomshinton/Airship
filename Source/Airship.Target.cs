// Airship Project - Tom Shinton 2018

using UnrealBuildTool;
using System.Collections.Generic;

public class AirshipTarget : TargetRules
{
	public AirshipTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Airship" } );

        if (Type == TargetRules.TargetType.Editor)
        {
            ExtraModuleNames.AddRange(new string[] { "AirEditor" });
        }
    }
}
