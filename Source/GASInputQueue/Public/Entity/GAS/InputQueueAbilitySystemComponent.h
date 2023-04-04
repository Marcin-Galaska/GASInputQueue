// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "InputQueueAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UInputQueueAbilitySystemComponent*, Instigator, float, UnmitigatedDamage, float, MitigatedDamage);

/**
 * 
 */
UCLASS()
class GASINPUTQUEUE_API UInputQueueAbilitySystemComponent : public UAbilitySystemComponent
{
private:
	GENERATED_BODY()
public:
	bool bAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;

	FGameplayAbilitySpec* CurrentActiveAbilityThatCanQueue = nullptr;
	FGameplayAbilitySpec* QueuedAbility = nullptr;

	bool bCommittingAbilityThatCannotQueue = false;
	bool bCommittingAbilityThatCanQueue = false;

	FReceivedDamageDelegate ReceivedDamage;
	
	virtual void ReceiveDamage(UInputQueueAbilitySystemComponent* Instigator, float UnmitigatedDamage, float MitigatedDamage);
};
