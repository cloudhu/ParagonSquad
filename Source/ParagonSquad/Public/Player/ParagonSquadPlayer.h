// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/NinjaGASPlayerCharacter.h"

#include "Interfaces/CombatSystemInterface.h"
#include "Interfaces/EquipmentSystemInterface.h"
#include "Interfaces/FactionMemberInterface.h"
#include "Interfaces/InputSetupProviderInterface.h"

#include "ParagonSquadPlayer.generated.h"

class UNinjaCombatEquipmentAdapterComponent;
class UNinjaEquipmentManagerComponent;
class USpringArmComponent;
class UCameraComponent;
class UNinjaCombatManagerComponent;
class UNinjaInputSetupDataAsset;
class UNinjaFactionComponent;

UCLASS(Blueprintable)
class AParagonSquadPlayer : public ANinjaGASPlayerCharacter, public ICombatSystemInterface, public IInputSetupProviderInterface, public IEquipmentSystemInterface, public IFactionMemberInterface
{
	GENERATED_BODY()

public:
	AParagonSquadPlayer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// -- Begin CombatSystem implementation
	virtual UNinjaCombatManagerComponent* GetCombatManager_Implementation() const override;
	virtual USceneComponent* GetCombatForwardReference_Implementation() const override;
	virtual USkeletalMeshComponent* GetCombatMesh_Implementation() const override;
	virtual UAnimInstance* GetCombatAnimInstance_Implementation() const override;
	virtual UActorComponent* GetWeaponManagerComponent_Implementation() const override;
	// -- End CombatSystem implementation

	// -- Begin Input Setup Provider implementation
	virtual TArray<UNinjaInputSetupDataAsset*> GetInputSetups_Implementation() const override;
	// -- End Input Setup Provider implementation

	// -- Begin EquipmentSystem implementation
	virtual UNinjaEquipmentManagerComponent* GetEquipmentManager_Implementation() const override;
	// -- End EquipmentSystem implementation

	// -- Begin Faction Member implementation
	virtual UNinjaFactionComponent* GetFactionComponent_Implementation() const override;
	// -- End Faction Member implementation
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Setup")
	TArray<UNinjaInputSetupDataAsset*> CharacterInputs;
	
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Combat Manager component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNinjaCombatManagerComponent> CombatManager;

	/** Forward Reference (Input and Combat integration). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> ForwardReference;

	/** Equipment Manager component. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNinjaEquipmentManagerComponent> EquipmentManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNinjaCombatEquipmentAdapterComponent> EquipmentWeaponManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNinjaFactionComponent> FactionManager;
};
