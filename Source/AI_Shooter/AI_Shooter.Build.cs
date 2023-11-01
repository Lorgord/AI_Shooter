// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AI_Shooter : ModuleRules
{
	public AI_Shooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "GameplayTasks", "NavigationSystem" });
	}
}
