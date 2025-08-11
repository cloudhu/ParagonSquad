// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/ParagonSquadPlayer.h"

#include "NinjaCombatTags.h"

#include "Camera/CameraComponent.h"

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/NinjaCombatCharacterMovementComponent.h"
#include "Components/NinjaCombatManagerComponent.h"
#include "Components/NinjaEquipmentManagerComponent.h"
#include "Components/NinjaFactionComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "NinjaCombatInventory/Public/Components/NinjaCombatEquipmentAdapterComponent.h"


AParagonSquadPlayer::AParagonSquadPlayer(const FObjectInitializer& ObjectInitializer): Super(
	ObjectInitializer.SetDefaultSubobjectClass<UNinjaCombatCharacterMovementComponent>(CharacterMovementComponentName))
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement -> use UNinjaCombatCharacterMovementComponent instead
	// GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	// GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	// GetCharacterMovement()->bConstrainToPlane = true;
	// GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CombatManager = CreateDefaultSubobject<UNinjaCombatManagerComponent>("CombatManager");

	ForwardReference = CreateDefaultSubobject<UArrowComponent>("ForwardReference");
	ForwardReference->ComponentTags.Add(Tag_Combat_Component_ForwardReference.GetTag().GetTagName());
	ForwardReference->SetVisibleFlag(false);
	ForwardReference->SetUsingAbsoluteRotation(true);
	ForwardReference->SetWorldRotation(FRotator::ZeroRotator);
	ForwardReference->SetArrowColor(FLinearColor::Green);
	ForwardReference->SetupAttachment(GetRootComponent());

	/** Equipment Manager component. */
	EquipmentManager = CreateDefaultSubobject<UNinjaEquipmentManagerComponent>(TEXT("EquipmentManager"));
	EquipmentWeaponManager = CreateDefaultSubobject<UNinjaCombatEquipmentAdapterComponent>(TEXT("EquipmentWeaponManager"));

	static const FName FactionComponentName = TEXT("FactionManager");
	FactionManager = CreateOptionalDefaultSubobject<UNinjaFactionComponent>(FactionComponentName);
}

void AParagonSquadPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

UNinjaCombatManagerComponent* AParagonSquadPlayer::GetCombatManager_Implementation() const
{
	return CombatManager;
}

USceneComponent* AParagonSquadPlayer::GetCombatForwardReference_Implementation() const
{
	return ForwardReference;
}

USkeletalMeshComponent* AParagonSquadPlayer::GetCombatMesh_Implementation() const
{
	return GetMesh();
}

UAnimInstance* AParagonSquadPlayer::GetCombatAnimInstance_Implementation() const
{
	return GetMesh()->GetAnimInstance();
}

UActorComponent* AParagonSquadPlayer::GetWeaponManagerComponent_Implementation() const
{
	return EquipmentWeaponManager;
}


TArray<UNinjaInputSetupDataAsset*> AParagonSquadPlayer::GetInputSetups_Implementation() const
{
	return CharacterInputs;
}

UNinjaEquipmentManagerComponent* AParagonSquadPlayer::GetEquipmentManager_Implementation() const
{
	return EquipmentManager;
}

UNinjaFactionComponent* AParagonSquadPlayer::GetFactionComponent_Implementation() const
{
	return FactionManager;
}
