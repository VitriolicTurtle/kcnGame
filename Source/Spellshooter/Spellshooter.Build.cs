// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Spellshooter : ModuleRules
{
	public Spellshooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine","Slate", "SlateCore", "InputCore", "HeadMountedDisplay", "GameplayAbilities", "UMG" });
	}
}
