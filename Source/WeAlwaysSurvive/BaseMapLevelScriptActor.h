// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Data/StringIntMapContainer.h"
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
	TMap<FString, UStringIntMapContainer*> DamagedActors;

protected:
	UFUNCTION(BlueprintCallable)
	void UpdateDamagedActors(FString damagedActor, FString damageCauser, int32 damage);

	UFUNCTION(BlueprintCallable)
	void HandleDeadActor(FString deadActor, float totalHealth, float totalExperience);

private:
	UStringIntMapContainer* CreateDamageCausers(FString damageCauser, int32 damage);
	void UpdateDamageCausers(TMap<FString, int32>& damageCausers, FString damageCauser, int32 damage);
	void RemoveDamagedActor(FString damagedActor);
	void SendExperience(TMap<FString, int32> damageCausers, float totalHealth, float totalExperience);
	AActor* FindExperienceReceiverByName(const FString& actorName);
};
