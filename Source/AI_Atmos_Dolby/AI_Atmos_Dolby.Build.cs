// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class AI_Atmos_Dolby : ModuleRules
{
	public AI_Atmos_Dolby(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", 
                                                            "EnhancedInput", "UMG", "Slate", "SlateCore", "Json", "Projects" });


    }
}
