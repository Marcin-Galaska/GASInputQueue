// Fill out your copyright notice in the Description page of Project Settings.

#include "Entity/GAS/InputQueueGameplayAbility.h"
#include <ciso646>
#include "AbilitySystemComponent.h"
#include "Entity/GAS/InputQueueAbilitySystemComponent.h"
#include "Entity/InputQueue/InputQueueAnimNotifyState.h"
#include "Entity/Playable/InputQueuePlayable.h"

UInputQueueGameplayAbility::UInputQueueGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Dead")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")));

	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Activatable")));
}

void UInputQueueGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	if(bActivateAbilityOnGranted)
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
}

bool UInputQueueGameplayAbility::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, FGameplayTagContainer* OptionalRelevantTags)
{
	auto* OwningAbilitySystemComponent = Cast<UInputQueueAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	
	//When we are trying to commit an ability that is not queueable or currently committing an ability that cannot queue.
	if((OwningAbilitySystemComponent->CurrentActiveAbilityThatCanQueue and !this->bIsAbilityQueueable and OwningAbilitySystemComponent->bCommittingAbilityThatCanQueue)
		or OwningAbilitySystemComponent->bCommittingAbilityThatCannotQueue)
	{
		this->CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		
		return false;
	}

	//When we try to commit a queueable ability while an ability that can queue is committing AND the input queue is active, we queue it.
	if(UInputQueueAnimNotifyState::InQueueWindow() and this->bIsAbilityQueueable and OwningAbilitySystemComponent->CurrentActiveAbilityThatCanQueue)
	{
		//We do not want the ability to trigger instantly, but rather get stored until the queue window ends.
		this->CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		this->InputPressed(Handle, ActorInfo, ActivationInfo);
		
		return false;
	}

	OwningAbilitySystemComponent->CurrentActiveAbilityThatCanQueue = nullptr;
	
	//When not in queue window, meaning we're not queueing this ability and instead committing it now.
	if(!UInputQueueAnimNotifyState::InQueueWindow())
	{
		if(this->bCanAbilityQueue)
		{
			const auto CurrentAbilitySpec = this->GetCurrentAbilitySpec();
			OwningAbilitySystemComponent->CurrentActiveAbilityThatCanQueue = CurrentAbilitySpec;
			OwningAbilitySystemComponent->bCommittingAbilityThatCanQueue = true;
		}
		else
			OwningAbilitySystemComponent->bCommittingAbilityThatCannotQueue = true;
	}
	
	return Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);
}

void UInputQueueGameplayAbility::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	auto* OwningAbilitySystemComponent = Cast<UInputQueueAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	
	//Called when a queueable ability is called outside the queue window.
	if(this->bCanAbilityQueue and !UInputQueueAnimNotifyState::InQueueWindow() and this->IsActive())
		this->CancelAbility(Handle, ActorInfo, ActivationInfo, true);

	//If ability queueable, queue it.
	if(this->bIsAbilityQueueable and OwningAbilitySystemComponent->CurrentActiveAbilityThatCanQueue
		and !OwningAbilitySystemComponent->QueuedAbility and UInputQueueAnimNotifyState::InQueueWindow())
	{
		const auto QueuedAbilitySpec = this->GetCurrentAbilitySpec();
		OwningAbilitySystemComponent->QueuedAbility = QueuedAbilitySpec;
	}
}

void UInputQueueGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	auto* OwningAbilitySystemComponent = Cast<UInputQueueAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());

	if(this->bCanAbilityQueue)
		OwningAbilitySystemComponent->bCommittingAbilityThatCanQueue = false;
	else
	{
		OwningAbilitySystemComponent->bCommittingAbilityThatCannotQueue = false;
		
		if(!bWasCancelled)
			OwningAbilitySystemComponent->CancelAbilities(new FGameplayTagContainer(FGameplayTag::RequestGameplayTag(FName("Ability.Activatable"))),
					nullptr, nullptr);
	}
	
	if(this->bIsAbilityQueueable)
		OwningAbilitySystemComponent->QueuedAbility = nullptr;
}

void UInputQueueGameplayAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}
