// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ParagonSquadPlayerController.generated.h"

class UNinjaInputManagerComponent;

UCLASS()
class AParagonSquadPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AParagonSquadPlayerController(const FObjectInitializer& ObjectInitializer);

private:

	/** Manages player input, using Enhanced Input/Ninja Input. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess=true))
	TObjectPtr<UNinjaInputManagerComponent> InputManager;
};


