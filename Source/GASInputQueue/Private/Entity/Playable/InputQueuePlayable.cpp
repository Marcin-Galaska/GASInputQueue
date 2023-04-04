// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Playable/InputQueuePlayable.h"
#include <ciso646>
#include "GameplayEffectTypes.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Entity/GAS/InputQueueAbilitySystemComponent.h"
#include "Entity/GAS/InputQueueAttributeSet.h"
#include "Entity/GAS/InputQueueGameplayAbility.h"
#include "Game/InputQueuePlayerController.h"
#include "Game/InputQueuePlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

void AInputQueuePlayable::Turn(float Value)
{
	if(IsAlive())
		AddControllerYawInput(Value);
}

void AInputQueuePlayable::LookUp(float Value)
{
	if(IsAlive())
		AddControllerPitchInput(Value);
}

void AInputQueuePlayable::LookUpRate(float Value)
{
	if(IsAlive())
		AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->DeltaTimeSeconds);
}

void AInputQueuePlayable::TurnRate(float Value)
{
	if(IsAlive())
		AddControllerYawInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
}

void AInputQueuePlayable::MoveForward(float Value)
{
	if(IsAlive())
		AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0)), Value);
}

void AInputQueuePlayable::MoveRight(float Value)
{
	if(IsAlive())
		AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, 0)), Value);
}

void AInputQueuePlayable::BindASCInput()
{
	if(!bASCInputBound and AbilitySystemComponent.IsValid() and IsValid(InputComponent))
	{
		//Additional inputs, like Ability1 or Basic, are automatically bound.
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds
		(
			"Confirm","Cancel", "EInputQueueAbilityInputID",
			static_cast<int32>(EIQAbilityInputID::Confirm),static_cast<int32>(EIQAbilityInputID::Cancel)
		));
		
		bASCInputBound = true;
	}
}

void AInputQueuePlayable::InitializeASC(AInputQueuePlayerState* TempPlayerState)
{
	//Initialize GAS
	AbilitySystemComponent = Cast<UInputQueueAbilitySystemComponent>(TempPlayerState->GetAbilitySystemComponent());
	TempPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(TempPlayerState, this);
	AttributeSet = TempPlayerState->GetAttributeSet();
	
	AbilitySystemComponent->SetTagMapCount(DeadTag, 0);
	
	InitializeAttributes();
	
	SetCurrentHealth(GetMaxHealth());
	SetCurrentStamina(GetMaxStamina());
}

void AInputQueuePlayable::BeginPlay()
{
	Super::BeginPlay();

	Controller->SetControlRotation(FRotator(180, 0, 0));

	//Save starting camera settings
	//Useful when you make abilities that change the camera position
	StartingCameraBoomArmLength = CameraBoom->TargetArmLength;
	StartingCameraBoomLocation = CameraBoom->GetRelativeLocation();
	StartingCameraBoomRotation = CameraBoom->GetComponentRotation();
}

//Replication
void AInputQueuePlayable::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if(AInputQueuePlayerState* TempPlayerState = GetPlayerState<AInputQueuePlayerState>())
	{
		InitializeASC(TempPlayerState);
		BindASCInput();
	}
}

AInputQueuePlayable::AInputQueuePlayable(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0,0,70));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->FieldOfView = 80.0f;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

void AInputQueuePlayable::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	//Uncomment these when changing camera, e.x. when switching from isometric to third person
	PlayerInputComponent->BindAxis("MoveForward", this, &AInputQueuePlayable::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AInputQueuePlayable::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AInputQueuePlayable::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AInputQueuePlayable::LookUpRate);
	PlayerInputComponent->BindAxis("Turn", this, &AInputQueuePlayable::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &AInputQueuePlayable::TurnRate);

	BindASCInput();
}

void AInputQueuePlayable::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AInputQueuePlayable::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if(AInputQueuePlayerState* TempPlayerState = GetPlayerState<AInputQueuePlayerState>())
	{
		InitializeASC(TempPlayerState);
		AddStartupEffects();
		GiveAbilities();
	}
}

USpringArmComponent* AInputQueuePlayable::GetCameraBoom() const
{
	return CameraBoom;
}

UCameraComponent* AInputQueuePlayable::GetFollowCamera() const
{
	return FollowCamera;
}

float AInputQueuePlayable::GetStartingCameraBoomArmLength() const
{
	return StartingCameraBoomArmLength;
}

FVector AInputQueuePlayable::GetStartingCameraBoomLocation() const
{
	return StartingCameraBoomLocation;
}

FRotator AInputQueuePlayable::GetStartingCameraBoomRotation() const
{
	return StartingCameraBoomRotation;
}
