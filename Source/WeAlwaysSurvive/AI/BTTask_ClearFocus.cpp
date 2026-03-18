// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearFocus.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_ClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto aiController = OwnerComp.GetAIOwner();

	if (aiController == nullptr)
		return EBTNodeResult::Failed;

	aiController->ClearFocus(EAIFocusPriority::Gameplay);
	
	return EBTNodeResult::Succeeded;
}
