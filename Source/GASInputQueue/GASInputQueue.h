// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

//In your inputs in project settings use the member names, not DisplayNames.
//All entries, besides Confirm and Cancel, are automatically bound when the engine detects a input of the same name in the project settings.
UENUM(BlueprintType)
	enum class EIQAbilityInputID : uint8
{
	None UMETA(DisplayName = "None"),
	Confirm UMETA(DisplayName = "Confirm"),
	Cancel UMETA(DisplayName = "Cancel"),
	Basic UMETA(DisplayName = "Basic"),
	Ability1 UMETA(DisplayName = "Skill 1"),
	Ability2 UMETA(DisplayName = "Skill 2"),
	Ability3 UMETA(DisplayName = "Skill 3")
};