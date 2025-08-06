// Copyright Epic Games, Inc. All Rights Reserved.

#include "ParagonSquadGameMode.h"
#include "ParagonSquadPlayerController.h"
#include "ParagonSquadCharacter.h"
#include "UObject/ConstructorHelpers.h"

AParagonSquadGameMode::AParagonSquadGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AParagonSquadPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}