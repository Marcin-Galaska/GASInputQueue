// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Entity/GAS/InputQueueAttributeSet.h"
#include "GameFramework/PlayerState.h"
#include "InputQueuePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GASINPUTQUEUE_API AInputQueuePlayerState : public APlayerState, public IAbilitySystemInterface
{
private:
	GENERATED_BODY()
protected:
	UPROPERTY()
		class UInputQueueAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
		class UInputQueueAttributeSet* AttributeSet;

	FGameplayTag DeadTag;

	//Handles
	FDelegateHandle CurrentHealthChangedHandle;
	FDelegateHandle MaxHealthChangedHandle;
	FDelegateHandle CurrentStaminaChangedHandle;
	FDelegateHandle MaxStaminaChangedHandle;
	FDelegateHandle EntityLevelChangedHandle;
	FDelegateHandle PhysicalDamageChangedHandle;
	FDelegateHandle AbilityDamageChangedHandle;

	//Notifies
	virtual void CurrentHealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void CurrentStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void EntityLevelChanged(const FOnAttributeChangeData& Data);
	virtual void PhysicalDamageChanged(const FOnAttributeChangeData& Data);
	virtual void AbilityDamageChanged(const FOnAttributeChangeData& Data);

	//Called when we either acquire or lose the stun tag.
	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	virtual void BeginPlay() override;
public:
	AInputQueuePlayerState();
	
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	class UInputQueueAttributeSet* GetAttributeSet() const;

	UFUNCTION(BlueprintCallable, Category = "Player|PlayerState")
		bool IsAlive() const;
	UFUNCTION(BlueprintCallable, Category = "Player|PlayerState|UI")
		void ShowAbilityConfirmCancelText(bool ShowText);

	//Getters
	UFUNCTION(BlueprintCallable, Category = "Player|PlayerState|Attributes")
		float GetCurrentHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Player|PlayerState|Attributes")
		float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Player|PlayerState|Attributes")
		float GetCurrentStamina() const;
	UFUNCTION(BlueprintCallable, Category = "Player|PlayerState|Attributes")
		float GetMaxStamina() const;
	UFUNCTION(BlueprintCallable, Category = "Player|PlayerState|Attributes")
		int32 GetEntityLevel() const;
	UFUNCTION(BlueprintCallable, Category = "Player|PlayerState|Attributes")
		float GetPhysicalDamage() const;
	UFUNCTION(BlueprintCallable, Category = "Player|PlayerState|Attributes")
		float GetAbilityDamage() const;
};
