// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/GAS/InputQueueAttributeSet.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

void UInputQueueAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UInputQueueAttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInputQueueAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInputQueueAttributeSet, CurrentStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInputQueueAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInputQueueAttributeSet, EntityLevel, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInputQueueAttributeSet, PhysicalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UInputQueueAttributeSet, AbilityDamage, COND_None, REPNOTIFY_Always);
}

void UInputQueueAttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData& OldCurrentHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInputQueueAttributeSet, CurrentHealth, OldCurrentHealth);
}

void UInputQueueAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInputQueueAttributeSet, MaxHealth, OldMaxHealth);
}

void UInputQueueAttributeSet::OnRep_CurrentStamina(const FGameplayAttributeData& OldCurrentStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInputQueueAttributeSet, CurrentStamina, OldCurrentStamina);
}

void UInputQueueAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInputQueueAttributeSet, MaxStamina, OldMaxStamina);
}

void UInputQueueAttributeSet::OnRep_EntityLevel(const FGameplayAttributeData& OldEntityLevel)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInputQueueAttributeSet, EntityLevel, OldEntityLevel);
}

void UInputQueueAttributeSet::OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInputQueueAttributeSet, PhysicalDamage, OldPhysicalDamage);
}

void UInputQueueAttributeSet::OnRep_AbilityDamage(const FGameplayAttributeData& OldAbilityDamage)

{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UInputQueueAttributeSet, AbilityDamage, OldAbilityDamage);
}
