// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Data/StringFloatMapContainer.h"
#include "BaseMapLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class WEALWAYSSURVIVE_API ABaseMapLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, UStringFloatMapContainer*> DamagedActors;

protected:
	UFUNCTION(BlueprintCallable)
	void UpdateDamagedActors(FString damagedActor, FString damageCauser, float damage);

	UFUNCTION(BlueprintCallable)
	void HandleDeadActor(FString deadActor, float totalHealth, float totalExperience);

private:
	UStringFloatMapContainer* CreateDamageCausers(FString damageCauser, float damage);
	void UpdateDamageCausers(TMap<FString, float>& damageCausers, FString damageCauser, float damage);
	void RemoveDamagedActor(FString damagedActor);
	void SendExperience(TMap<FString, float> damageCausers, float totalHealth, float totalExperience);
	AActor* FindExperienceReceiverByName(const FString& actorName);
};
