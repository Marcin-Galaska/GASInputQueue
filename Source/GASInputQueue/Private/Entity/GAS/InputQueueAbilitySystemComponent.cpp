// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/GAS/InputQueueAbilitySystemComponent.h"

void UInputQueueAbilitySystemComponent::ReceiveDamage(UInputQueueAbilitySystemComponent* Instigator,
	float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(Instigator, UnmitigatedDamage, MitigatedDamage);
}
