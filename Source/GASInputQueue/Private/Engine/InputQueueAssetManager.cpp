// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/InputQueueAssetManager.h"
#include "AbilitySystemGlobals.h"

void UInputQueueAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	UAbilitySystemGlobals::Get().InitGlobalData();

	//This will appear in your output log if you have set this below '[/Script/Engine.Engine]' in 'Config/DefaultEngine.ini':
	//AssetManagerClassName=/Script/<Project Name>.<Asset Manager Class>
	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] %s() called."), *FString(__FUNCTION__));
}
