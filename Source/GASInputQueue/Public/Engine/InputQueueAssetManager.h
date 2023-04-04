// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "InputQueueAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class GASINPUTQUEUE_API UInputQueueAssetManager : public UAssetManager
{
private:
	GENERATED_BODY()
public:
	virtual void StartInitialLoading() override;
};
