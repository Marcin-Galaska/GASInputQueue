// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "InputQueueAbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "GASInputQueue/GASInputQueue.h"
#include "InputQueueGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GASINPUTQUEUE_API UInputQueueGameplayAbility : public UGameplayAbility
{
private:
	GENERATED_BODY()
public:
	UInputQueueGameplayAbility();

	//Ability keybind, must be filled in ability blueprint.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
	EIQAbilityInputID AbilityInputID = EIQAbilityInputID::None;

	//Whether this ability can be cancelled in order to commit a queued ability. If you want this to work, remember to put a queue window notify state in your ability montage.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Ability|InputQueue")
	bool bCanAbilityQueue = true;
	//Whether this ability can be queued, meaning pressing its input will make it trigger after the currently active ability (that can queue) finishes its queue window.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Ability|InputQueue")
	bool bIsAbilityQueueable = true;

	//Whether this ability should trigger immediately after being granted to the character.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Ability")
	bool bActivateAbilityOnGranted = false;
	
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, FGameplayTagContainer* OptionalRelevantTags) override;
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
};
