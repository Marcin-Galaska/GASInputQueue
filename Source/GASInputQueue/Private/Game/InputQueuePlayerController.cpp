// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/InputQueuePlayerController.h"
#include "AbilitySystemComponent.h"
#include "Game/InputQueuePlayerState.h"

void AInputQueuePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(const AInputQueuePlayerState* TempPlayerState = GetPlayerState<AInputQueuePlayerState>())
	{
		TempPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerState, InPawn);
	}
}
