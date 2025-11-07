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

        //string PluginPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../Plugins/LibTorchUE"));
        //string LibtorchPath = Path.Combine(PluginPath, "Source", "ThirdParty", "libtorch");

        //PublicIncludePaths.Add(Path.Combine(LibtorchPath, "include"));

        //// Link LibTorch libraries
        //PublicAdditionalLibraries.Add(Path.Combine(LibtorchPath, "lib", "torch.lib"));
        //PublicAdditionalLibraries.Add(Path.Combine(LibtorchPath, "lib", "c10.lib"));

        ////Runtime DLLs
        ////RuntimeDependencies.Add("$(BinaryOutputDir)/torch.dll", Path.Combine(LibtorchPath, "lib", "torch.dll"));
        ////RuntimeDependencies.Add("$(BinaryOutputDir)/c10.dll", Path.Combine(LibtorchPath, "lib", "c10.dll"));
        ////RuntimeDependencies.Add("$(BinaryOutputDir)/torch_cpu.dll", Path.Combine(LibtorchPath, "lib", "torch_cpu.dll"));
        ////RuntimeDependencies.Add("$(BinaryOutputDir)/torch_python.dll", Path.Combine(LibtorchPath, "lib", "torch_python.dll"));

        ////Required for LibTorch
        //bEnableExceptions = true;
        //bUseRTTI = true;
        //CppStandard = CppStandardVersion.Cpp17;





    }
}
