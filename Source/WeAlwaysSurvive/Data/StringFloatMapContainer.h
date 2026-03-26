// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StringFloatMapContainer.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class WEALWAYSSURVIVE_API UStringFloatMapContainer : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, float> Map;
};
