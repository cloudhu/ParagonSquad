// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ParagonSquad : ModuleRules
{
	public ParagonSquad(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(["Core", "CoreUObject", "Engine",  "NavigationSystem", "AIModule",  "EnhancedInput",
	        "GameplayMessageRuntime",
	        "NinjaGAS",
	        "NinjaInput",
	        // Ninja Combat
	        "CommonUI",
	        "GameplayAbilities",
	        "GameplayTags",
	        "GameplayTasks",
	        "InputCore",
	        "ModelViewViewModel",
	        "Niagara",
	        "NinjaCombat",
	        "NinjaCombatCamera",
	        "NinjaCombatCore",
	        "NinjaCombatActorPool",
	        "NinjaCombatUI",
	        "StructUtils",
	        // Ninja Inventory
	        "NinjaInventory",
	        "NinjaInventoryCore",
	        "NinjaInventoryEquipment",
	        "UMG",
	        "CommonInput"
        ]);
    }
}
