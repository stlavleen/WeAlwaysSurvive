// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSettings.generated.h"

/**
 * 
 */
UCLASS()
class WEALWAYSSURVIVE_API UGameSettings : public UObject
{
	GENERATED_BODY()

public:
	UGameSettings();
	
public:
	UPROPERTY(BlueprintReadWrite)
	FString SoundtracksFolderName;
};
