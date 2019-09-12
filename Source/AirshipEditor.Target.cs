// Airship Project - Tom Shinton 2018

using UnrealBuildTool;
using System.Collections.Generic;

public class AirshipEditorTarget : TargetRules
{
	public AirshipEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "AirEditor" } );
	}
}
