// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StringIntMapContainer.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class WEALWAYSSURVIVE_API UStringIntMapContainer : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, int32> Map;
};
