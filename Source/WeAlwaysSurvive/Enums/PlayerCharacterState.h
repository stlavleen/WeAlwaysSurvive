// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacterState.generated.h"
/**
 * 
 */

UENUM(BlueprintType)
enum class EPlayerCharacterState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Walking UMETA(DisplayName = "Walking"),
	Running UMETA(DisplayName = "Running")
};
