// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class AirshipTarget : TargetRules
{
	public AirshipTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Airship" } );
		ExtraModuleNames.AddRange( new string[] { "AirCore" } );

        if (Target.Type == TargetType.Editor)
        {
            ExtraModuleNames.AddRange(
                new string[]
                {
                    "AirEditor"
                });
        }
    }
}
