// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputQueuePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GASINPUTQUEUE_API AInputQueuePlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
