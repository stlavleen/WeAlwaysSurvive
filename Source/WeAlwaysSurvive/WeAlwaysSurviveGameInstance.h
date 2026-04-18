// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WeAlwaysSurviveGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WEALWAYSSURVIVE_API UWeAlwaysSurviveGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class UGameSettings* Settings;

public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	UGameSettings* GetSettings() const;

private:
	UFUNCTION()
	void BeginLoadingScreen(const FString& mapName);
};
