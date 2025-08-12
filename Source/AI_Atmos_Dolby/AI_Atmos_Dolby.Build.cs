// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AI_Atmos_Dolby : ModuleRules
{
	public AI_Atmos_Dolby(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
