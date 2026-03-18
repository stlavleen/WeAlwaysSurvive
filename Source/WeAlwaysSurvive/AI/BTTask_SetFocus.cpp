// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetFocus.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_SetFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto aiController = OwnerComp.GetAIOwner();

	if (aiController == nullptr)
		return EBTNodeResult::Failed;

	auto blackboard = OwnerComp.GetBlackboardComponent();

	if (blackboard == nullptr)
		return EBTNodeResult::Failed;

	const auto targetActor = Cast<AActor>(blackboard->GetValueAsObject(TargetKey.SelectedKeyName));

	aiController->SetFocus(targetActor);

	return EBTNodeResult::Succeeded;
}
