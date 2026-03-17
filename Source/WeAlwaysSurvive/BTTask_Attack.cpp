// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "EnemyAIController.h"
#include "Characters/EnemyCharacter.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto aiController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	if (aiController == nullptr)
		return EBTNodeResult::Failed;

	aiController->Attack();
	
	return EBTNodeResult::Succeeded;
}
