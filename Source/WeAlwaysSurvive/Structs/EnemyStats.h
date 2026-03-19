// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyStats.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct WEALWAYSSURVIVE_API FEnemyStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> AttacksDamage;

	FEnemyStats();
	FEnemyStats(int32 health, int32 level, TArray<int32> attacksDamage);
};
