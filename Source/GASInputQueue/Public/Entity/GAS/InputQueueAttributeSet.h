// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "InputQueueAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class GASINPUTQUEUE_API UInputQueueAttributeSet : public UAttributeSet
{
private:
	GENERATED_BODY()
public:
	//Used for attribute replication (multiplayer).
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//Default attributes - health, stamina, level and two types of damage.
	//These are examples, use whatever attributes you desire.
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health", ReplicatedUsing = OnRep_CurrentHealth)
		FGameplayAttributeData CurrentHealth;
		ATTRIBUTE_ACCESSORS(UInputQueueAttributeSet, CurrentHealth)
	UFUNCTION()
		virtual void OnRep_CurrentHealth(const FGameplayAttributeData& OldCurrentHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health", ReplicatedUsing = OnRep_MaxHealth)
		FGameplayAttributeData MaxHealth;
		ATTRIBUTE_ACCESSORS(UInputQueueAttributeSet, MaxHealth)
	UFUNCTION()
		virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Stamina", ReplicatedUsing = OnRep_CurrentStamina)
		FGameplayAttributeData CurrentStamina;
		ATTRIBUTE_ACCESSORS(UInputQueueAttributeSet, CurrentStamina)
	UFUNCTION()
		virtual void OnRep_CurrentStamina(const FGameplayAttributeData& OldCurrentStamina);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Stamina", ReplicatedUsing = OnRep_MaxStamina)
		FGameplayAttributeData MaxStamina;
		ATTRIBUTE_ACCESSORS(UInputQueueAttributeSet, MaxStamina)
	UFUNCTION()
		virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|EntityLevel", ReplicatedUsing = OnRep_EntityLevel)
		FGameplayAttributeData EntityLevel;
		ATTRIBUTE_ACCESSORS(UInputQueueAttributeSet, EntityLevel)
	UFUNCTION()
		virtual void OnRep_EntityLevel(const FGameplayAttributeData& OldEntityLevel);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Damage", ReplicatedUsing = OnRep_PhysicalDamage)
		FGameplayAttributeData PhysicalDamage;
		ATTRIBUTE_ACCESSORS(UInputQueueAttributeSet, PhysicalDamage)
	UFUNCTION()
		virtual void OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Damage", ReplicatedUsing = OnRep_AbilityDamage)
		FGameplayAttributeData AbilityDamage;
		ATTRIBUTE_ACCESSORS(UInputQueueAttributeSet, AbilityDamage)
	UFUNCTION()
		virtual void OnRep_AbilityDamage(const FGameplayAttributeData& OldAbilityDamage);
};
