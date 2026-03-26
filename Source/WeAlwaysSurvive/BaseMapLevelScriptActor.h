// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "BaseMapLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class WEALWAYSSURVIVE_API ABaseMapLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	AActor* FindExperienceReceiverByName(const FString& actorName);

	UFUNCTION(BlueprintCallable)
	void SendExperience(TMap<FString, int32> damageCausers, int32 totalExperience);
};
