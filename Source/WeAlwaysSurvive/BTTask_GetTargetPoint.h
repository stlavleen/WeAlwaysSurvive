// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GetTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class WEALWAYSSURVIVE_API UBTTask_GetTargetPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Blackboard")
	FBlackboardKeySelector TargetPointKey;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
