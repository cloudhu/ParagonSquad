// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/NinjaFactionPlayerController.h"
#include "GameplayPlayerController.generated.h"

class UNinjaInputManagerComponent;

UCLASS()
class AGameplayPlayerController : public ANinjaFactionPlayerController
{
	GENERATED_BODY()

public:
	AGameplayPlayerController();

private:

	/** Manages player input, using Enhanced Input/Ninja Input. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess=true))
	TObjectPtr<UNinjaInputManagerComponent> InputManager;
};


