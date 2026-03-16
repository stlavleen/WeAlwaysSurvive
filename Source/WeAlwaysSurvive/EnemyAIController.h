// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

struct FAIStimulus;
struct FActorPerceptionUpdateInfo;
class UBehaviorTree;

/**
 * 
 */
UCLASS()
class WEALWAYSSURVIVE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy AI")
	UBehaviorTree* BehaviorTree;

	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
	void OnTargetPerceptionUpdate(AActor* actor, FAIStimulus stimulus);
};
