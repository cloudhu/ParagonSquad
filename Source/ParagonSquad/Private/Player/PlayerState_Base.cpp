// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerState_Base.h"

#include "Components/NinjaInventoryManagerComponent.h"

APlayerState_Base::APlayerState_Base(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	InventoryManager = CreateDefaultSubobject<UNinjaInventoryManagerComponent>(TEXT("InventoryManager"));
	
}

UNinjaInventoryManagerComponent* APlayerState_Base::GetInventoryManager_Implementation() const
{
	return InventoryManager;
}
