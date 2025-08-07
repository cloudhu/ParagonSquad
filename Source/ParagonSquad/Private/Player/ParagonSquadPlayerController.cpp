// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/ParagonSquadPlayerController.h"
#include "Components/NinjaInputManagerComponent.h"

AParagonSquadPlayerController::AParagonSquadPlayerController(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	static const FName InputManagerName = FName("InputManager");
	InputManager = CreateDefaultSubobject<UNinjaInputManagerComponent>(InputManagerName);
}
