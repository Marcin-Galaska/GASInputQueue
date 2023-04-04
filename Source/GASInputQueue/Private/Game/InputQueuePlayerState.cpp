// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/InputQueuePlayerState.h"
#include "GameplayEffectTypes.h"
#include "Entity/GAS/InputQueueAbilitySystemComponent.h"
#include "Entity/GAS/InputQueueAttributeSet.h"

void AInputQueuePlayerState::CurrentHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] Current Health Changed. (%s() called)."), *FString(__FUNCTION__));
}

void AInputQueuePlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] Max Health Changed. (%s() called)."), *FString(__FUNCTION__));
}

void AInputQueuePlayerState::CurrentStaminaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] Current Stamina Changed. (%s() called)."), *FString(__FUNCTION__));
}

void AInputQueuePlayerState::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] Max Stamina Changed. (%s() called)."), *FString(__FUNCTION__));
}

void AInputQueuePlayerState::EntityLevelChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] Entity Level Changed. (%s() called)."), *FString(__FUNCTION__));
}

void AInputQueuePlayerState::PhysicalDamageChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] Physical Damage Changed. (%s() called)."), *FString(__FUNCTION__));
}

void AInputQueuePlayerState::AbilityDamageChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] Ability Damage Changed. (%s() called)."), *FString(__FUNCTION__));
}

void AInputQueuePlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if(NewCount > 0)
	{
		//Cancels normal abilities
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		//Stops uncancellable abilities from cancelling
		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCancelledByStun")));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
}

void AInputQueuePlayerState::BeginPlay()
{
	Super::BeginPlay();

	//Boilerplate
	if(AbilitySystemComponent)
	{
		CurrentHealthChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetCurrentHealthAttribute()).AddUObject(this,
			&AInputQueuePlayerState::CurrentHealthChanged);
		MaxHealthChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddUObject(this,
			&AInputQueuePlayerState::MaxHealthChanged);
		CurrentStaminaChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetCurrentStaminaAttribute()).AddUObject(this,
			&AInputQueuePlayerState::CurrentStaminaChanged);
		CurrentStaminaChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetCurrentStaminaAttribute()).AddUObject(this,
			&AInputQueuePlayerState::CurrentStaminaChanged);
		EntityLevelChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetEntityLevelAttribute()).AddUObject(this,
			&AInputQueuePlayerState::EntityLevelChanged);
		PhysicalDamageChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetEntityLevelAttribute()).AddUObject(this,
			&AInputQueuePlayerState::PhysicalDamageChanged);
		AbilityDamageChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetEntityLevelAttribute()).AddUObject(this,
			&AInputQueuePlayerState::AbilityDamageChanged);

		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this,
			&AInputQueuePlayerState::StunTagChanged);
	}
}

AInputQueuePlayerState::AInputQueuePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UInputQueueAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed); //If you are making a multiplayer project, best set it to Minimal.

	AttributeSet = CreateDefaultSubobject<UInputQueueAttributeSet>(TEXT("BaseAttributeSet"));

	NetUpdateFrequency = 100.0f;
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent* AInputQueuePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UInputQueueAttributeSet* AInputQueuePlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

bool AInputQueuePlayerState::IsAlive() const
{
	return (GetCurrentHealth() > 0.0f) ? true : false;
}

void AInputQueuePlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	//This function helps you display ability confirmation info on your HUD.
	//Fill it only if you plan on making an user interface.
}

float AInputQueuePlayerState::GetCurrentHealth() const
{
	return AttributeSet->GetCurrentHealth();
}

float AInputQueuePlayerState::GetMaxHealth() const
{
	return AttributeSet->GetMaxStamina();
}

float AInputQueuePlayerState::GetCurrentStamina() const
{
	return AttributeSet->GetCurrentStamina();
}

float AInputQueuePlayerState::GetMaxStamina() const
{
	return AttributeSet->GetMaxStamina();
}

int32 AInputQueuePlayerState::GetEntityLevel() const
{
	return AttributeSet->GetEntityLevel();
}

float AInputQueuePlayerState::GetPhysicalDamage() const
{
	return AttributeSet->GetPhysicalDamage();
}

float AInputQueuePlayerState::GetAbilityDamage() const
{
	return AttributeSet->GetAbilityDamage();
}