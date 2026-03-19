// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStats.h"

FEnemyStats::FEnemyStats() 
	: FEnemyStats(0, 0, {})
{
}

FEnemyStats::FEnemyStats(int32 health, int32 level, TArray<int32> attacksDamage) 
	: Health(health), Level(level), AttacksDamage(attacksDamage)
{
}
