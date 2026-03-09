// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class WEALWAYSSURVIVE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy AI")
	UBehaviorTree* BehaviorTree;
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
