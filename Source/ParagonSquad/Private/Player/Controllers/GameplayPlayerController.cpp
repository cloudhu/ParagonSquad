// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/Controllers/GameplayPlayerController.h"
#include "Components/NinjaInputManagerComponent.h"

AGameplayPlayerController::AGameplayPlayerController()
{
	static const FName InputManagerName = FName("InputManager");
	InputManager = CreateDefaultSubobject<UNinjaInputManagerComponent>(InputManagerName);
}
