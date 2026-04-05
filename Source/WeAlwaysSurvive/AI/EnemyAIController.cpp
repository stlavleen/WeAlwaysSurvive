// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "WeAlwaysSurvive/Characters/PlayerCharacter.h"
#include "WeAlwaysSurvive/Characters/EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"

AEnemyAIController::AEnemyAIController() : BehaviorTree(nullptr)
{
	auto senseConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseConfig_Sight"));
	senseConfig->SightRadius = 2000;
	senseConfig->LoseSightRadius = 2700;
	senseConfig->PeripheralVisionAngleDegrees = 90;
	senseConfig->DetectionByAffiliation.bDetectEnemies = true;
	senseConfig->DetectionByAffiliation.bDetectNeutrals = true;
	senseConfig->DetectionByAffiliation.bDetectFriendlies = true;
	senseConfig->SetMaxAge(1.f);

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	PerceptionComponent->ConfigureSense(*senseConfig);
	PerceptionComponent->SetDominantSense(senseConfig->GetSenseImplementation());
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdate);
	PerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionForget);
}

AEnemyCharacter* AEnemyAIController::GetEnemyCharacter() const
{
	return Cast<AEnemyCharacter>(GetCharacter());
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ensureMsgf(BehaviorTree, TEXT("Behavior tree has not been set")))
		RunBehaviorTree(BehaviorTree);

	auto enemyCharacter = GetEnemyCharacter();

	if (enemyCharacter != nullptr)
		enemyCharacter->OnDeath.AddDynamic(this, &AEnemyAIController::OnCharacterDeath);
}

void AEnemyAIController::OnUnPossess()
{
	BrainComponent->StopLogic("OnUnPossess");

	Super::OnUnPossess();
}

void AEnemyAIController::OnTargetPerceptionUpdate(AActor* actor, FAIStimulus stimulus)
{
	const auto senseID = UAISense::GetSenseID<UAISense_Sight>();
	auto playerCharacter = Cast<APlayerCharacter>(actor);

	if (senseID == stimulus.Type && stimulus.WasSuccessfullySensed() && playerCharacter != nullptr)
	{
		auto blackboardComp = GetBlackboardComponent();
		blackboardComp->SetValueAsObject(PlayerActorKeyName, playerCharacter);
	}
}

void AEnemyAIController::OnTargetPerceptionForget(AActor* actor)
{
	auto playerCharacter = Cast<APlayerCharacter>(actor);
	
	if (playerCharacter != nullptr) 
	{
		auto blackboardComp = GetBlackboardComponent();
		blackboardComp->SetValueAsObject(PlayerActorKeyName, nullptr);
	}
}

void AEnemyAIController::OnCharacterDeath(AActor* sender, float totalHealth, float totalExperience)
{
	ClearFocus(EAIFocusPriority::Gameplay);
	CleanupBrainComponent();
}
