// Fill out your copyright notice in the Description page of Project Settings.


#include "WeAlwaysSurviveGameInstance.h"
#include "Data/GameSettings.h"
#include "MoviePlayer.h"

void UWeAlwaysSurviveGameInstance::Init()
{
	Super::Init();
	Settings = NewObject<UGameSettings>();
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UWeAlwaysSurviveGameInstance::BeginLoadingScreen);
}

UGameSettings* UWeAlwaysSurviveGameInstance::GetSettings() const
{
	return Settings;
}

void UWeAlwaysSurviveGameInstance::BeginLoadingScreen(const FString& mapName)
{
	if (!IsDedicatedServerInstance()) 
	{
		FLoadingScreenAttributes loadingScreen;
		loadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		loadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

		GetMoviePlayer()->SetupLoadingScreen(loadingScreen);
	}
}


