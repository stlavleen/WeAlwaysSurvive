// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStats.h"

FPlayerStats::FPlayerStats() 
	: FPlayerStats(0, 0, 0, 0)
{
}

FPlayerStats::FPlayerStats(int32 health, int32 stamina, int32 experience, int32 level)
	: Health(health), Stamina(stamina), Experience(experience), Level(level)
{
}
