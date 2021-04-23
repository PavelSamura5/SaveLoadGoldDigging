// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GoldenRunExample : ModuleRules
{
	public GoldenRunExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
    }
}
