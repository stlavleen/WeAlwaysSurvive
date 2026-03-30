// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

struct FAIStimulus;
class AEnemyCharacter;

/**
 * 
 */
UCLASS()
class WEALWAYSSURVIVE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

	UFUNCTION(BlueprintCallable)
	AEnemyCharacter* GetEnemyCharacter() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "Enemy AI")
	FName PlayerActorKeyName = "PlayerActor";

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnCharacterDeath(AActor* sender, float totalHealth, float totalExperience);

private:
	UFUNCTION()
	void OnTargetPerceptionUpdate(AActor* actor, FAIStimulus stimulus);

	UFUNCTION()
	void OnTargetPerceptionForget(AActor* actor);
};
