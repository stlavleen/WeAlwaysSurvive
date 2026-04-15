// Fill out your copyright notice in the Description page of Project Settings.


#include "WeAlwaysSurviveGameInstance.h"
#include "Data/GameSettings.h"

void UWeAlwaysSurviveGameInstance::Init()
{
	Super::Init();
	Settings = NewObject<UGameSettings>();
}

UGameSettings* UWeAlwaysSurviveGameInstance::GetSettings() const
{
	return Settings;
}