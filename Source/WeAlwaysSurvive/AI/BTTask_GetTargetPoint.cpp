// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetTargetPoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_GetTargetPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto blackboardComponent = OwnerComp.GetBlackboardComponent();

	if (blackboardComponent == nullptr)
		return EBTNodeResult::Failed;

	const auto aiController = OwnerComp.GetAIOwner();

	if (aiController == nullptr)
		return EBTNodeResult::Failed;

	const auto controlledCharacter = aiController->GetPawn();

	if (controlledCharacter == nullptr)
		return EBTNodeResult::Failed;

	const auto currentLocation = controlledCharacter->GetActorLocation();
	const auto rand2DPoint = FMath::RandPointInCircle(1000);
	const auto targetPoint = currentLocation + FVector(rand2DPoint.X, rand2DPoint.Y, 0);

	blackboardComponent->SetValueAsVector(TargetPointKey.SelectedKeyName, targetPoint);

	return EBTNodeResult::Succeeded;
}
