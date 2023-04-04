// Fill out your copyright notice in the Description page of Project Settings.

#include "Entity/InputQueue/InputQueueAnimNotifyState.h"
#include <iso646.h>
#include "Entity/GAS/InputQueueGameplayAbility.h"
#include "Entity/Playable/InputQueuePlayable.h"
#include "Kismet/GameplayStatics.h"

void UInputQueueAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	bInQueueWindow = false;
	
	if(auto* OwningCharacter = Cast<AInputQueuePlayable>(MeshComp->GetOwner()))
	{
		auto* OwningActorAbilitySystemComponent = Cast<UInputQueueAbilitySystemComponent>(OwningCharacter->GetAbilitySystemComponent());

		//The queue window has ended. If we have queued an ability we now want to end the current one and activate the queued one.
		if(OwningActorAbilitySystemComponent and OwningActorAbilitySystemComponent->QueuedAbility and OwningActorAbilitySystemComponent->CurrentActiveAbilityThatCanQueue)
		{
			const auto temp = OwningActorAbilitySystemComponent->QueuedAbility->Handle;
			
			OwningActorAbilitySystemComponent->CancelAbilities(new FGameplayTagContainer(FGameplayTag::RequestGameplayTag(FName("Ability.Activatable"))),
				nullptr, nullptr);
			
			OwningActorAbilitySystemComponent->TryActivateAbility(temp);
		}
	}
}

void UInputQueueAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	bInQueueWindow = true;
}
