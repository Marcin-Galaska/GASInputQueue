// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Entity/GAS/InputQueueAbilitySystemComponent.h>
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "InputQueueAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class GASINPUTQUEUE_API UInputQueueAnimNotifyState : public UAnimNotifyState
{
private:
	GENERATED_BODY()
protected:
	inline static bool bInQueueWindow = false;
public:
	inline static bool InQueueWindow() { return bInQueueWindow; };

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
};
