// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "GASInputQueue/GASInputQueue.h"
#include "InputQueueEntity.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEntityDiedDelegate, AInputQueueEntity*, Entity);

UCLASS()
class GASINPUTQUEUE_API AInputQueueEntity : public ACharacter, public IAbilitySystemInterface
{
private:
	GENERATED_BODY()
protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The very core of this class.
	TWeakObjectPtr<class UInputQueueAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UInputQueueAttributeSet> AttributeSet;

	//Tags
	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	//Editor properties. Don't forget to set these in your blueprint derived class.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Entity|GAS|Attributes")
		TSubclassOf<class UGameplayEffect> DefaultAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Entity|GAS|Effects")
		TArray< TSubclassOf<class UGameplayEffect> > StartupEffects;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Entity|GAS|Abilities")
		TArray< TSubclassOf<class UInputQueueGameplayAbility> > EntityAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Entity")
		FText EntityName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Entity|Animations")
		UAnimMontage* DeathMontage;

	//Helper functions
	virtual void GiveAbilities();
	virtual void InitializeAttributes();
	virtual void AddStartupEffects();

	//Setters
	virtual void SetCurrentHealth(const float& NewCurrentHealth);
	virtual void SetMaxHealth(const float& NewMaxHealth);
	virtual void SetCurrentStamina(const float& NewCurrentStamina);
	virtual void SetMaxStamina(const float& NewMaxStamina);
	virtual void SetEntityLevel(const float& NewEntityLevel);
	virtual void SetPhysicalDamage(const float& NewPhysicalDamage);
	virtual void SetAbilityDamage(const float& NewAbilityDamage);

public:
	//Sets default values for this character's properties
	AInputQueueEntity(const class FObjectInitializer& ObjectInitializer);
	
	//Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Mandatory getter
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//Functions used when creating real abilities.
	UPROPERTY(BlueprintAssignable, Category="Entity")
		FEntityDiedDelegate OnDied;
	UFUNCTION(BlueprintCallable, Category="Entity")
		virtual bool IsAlive() const;
	UFUNCTION(BlueprintCallable, Category="Entity|GAS|Abilities")
		virtual int32 GetAbilityLevel(EIQAbilityInputID ID) const;

	virtual void RemoveAbilities();
	virtual void Die();
	
	UFUNCTION(BlueprintCallable, Category = "Entity")
		virtual void FinishDying();

	//Getters
	UFUNCTION(BlueprintCallable, Category="Entity|GAS|Attributes")
		float GetCurrentHealth() const;
	UFUNCTION(BlueprintCallable, Category="Entity|GAS|Attributes")
		float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category="Entity|GAS|Attributes")
		float GetCurrentStamina() const;
	UFUNCTION(BlueprintCallable, Category="Entity|GAS|Attributes")
		float GetMaxStamina() const;
	UFUNCTION(BlueprintCallable, Category="Entity|GAS|Attributes")
		float GetEntityLevel() const;
	UFUNCTION(BlueprintCallable, Category="Entity|GAS|Attributes")
		float GetPhysicalDamage() const;
	UFUNCTION(BlueprintCallable, Category="Entity|GAS|Attributes")
		float GetAbilityDamage() const;
};