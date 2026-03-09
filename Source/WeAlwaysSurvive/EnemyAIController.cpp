// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ensureMsgf(BehaviorTree, TEXT("Behavior tree has not been set")))
		RunBehaviorTree(BehaviorTree);
}
