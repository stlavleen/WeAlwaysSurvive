// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FileSystemHelper.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class WEALWAYSSURVIVE_API UFileSystemHelper : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	TArray<FString> GetFilesNames(const FString folderName) const;

//private:
	UFUNCTION(BlueprintCallable)
	FString GetGamePath() const;
};
