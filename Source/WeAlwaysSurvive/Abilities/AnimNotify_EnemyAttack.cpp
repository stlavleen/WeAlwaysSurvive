// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_EnemyAttack.h"
#include "WeAlwaysSurvive/Characters/EnemyCharacter.h"
#include "AIController.h"

bool UAnimNotify_EnemyAttack::Attack(USkeletalMeshComponent* meshComp, int32 attackIndex)
{
	auto enemyCharacter = Cast<AEnemyCharacter>(meshComp->GetOwner());

	if (enemyCharacter == nullptr)
		return false;

	auto aiController = enemyCharacter->GetController<AAIController>();

	if (aiController == nullptr)
		return false;

	auto focusActor = aiController->GetFocusActor();

	if (focusActor == nullptr)
		return false;

	return enemyCharacter->Attack(focusActor, attackIndex);
}
