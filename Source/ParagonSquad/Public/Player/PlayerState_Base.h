// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NinjaGASPlayerState.h"

#include "Interfaces/InventorySystemInterface.h"

#include "PlayerState_Base.generated.h"

class UNinjaInventoryManagerComponent;
/**
 * @class APlayerState_Base
 * @brief Base player state class, inheriting from ANinjaGASPlayerState, designed to hold and manage the state of a player in the game.
 *
 * This class is responsible for maintaining and providing access to essential player state information, including an inventory management component.
 */
UCLASS(Blueprintable)
class PARAGONSQUAD_API APlayerState_Base : public ANinjaGASPlayerState, public IInventorySystemInterface
{

	GENERATED_BODY()
	
public:
	APlayerState_Base(const FObjectInitializer& ObjectInitializer);

	// -- Begin InventorySystem implementation
	virtual UNinjaInventoryManagerComponent* GetInventoryManager_Implementation() const override;
	// -- End InventorySystem implementation
private:

	/** Inventory Manager component. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNinjaInventoryManagerComponent> InventoryManager;
};