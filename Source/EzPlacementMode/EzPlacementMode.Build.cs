// Copyright 2023 Yoshikazu Azechi All Rights Reserved.

using UnrealBuildTool;

public class EzPlacementMode : ModuleRules
{
	public EzPlacementMode(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.AddRange(
			new string[] 
			{
				"EzPlacementMode/Private",
			});

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			});
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UnrealEd",
				"DeveloperSettings",
				"PlacementMode"
			});
	}
}
