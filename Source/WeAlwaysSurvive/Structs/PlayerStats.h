// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStats.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct WEALWAYSSURVIVE_API FPlayerStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Experience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	FPlayerStats();
	FPlayerStats(int32 health, int32 stamina, int32 experience, int32 level);
};
