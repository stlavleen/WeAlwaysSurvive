// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"

AEnemyAIController::AEnemyAIController()
{
	auto senseConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseConfig_Sight"));
	senseConfig->SightRadius = 2000;
	senseConfig->LoseSightRadius = 2700;
	senseConfig->PeripheralVisionAngleDegrees = 90;
	senseConfig->DetectionByAffiliation.bDetectEnemies = true;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	PerceptionComponent->ConfigureSense(*senseConfig);
	PerceptionComponent->SetDominantSense(senseConfig->GetSenseImplementation());
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ensureMsgf(BehaviorTree, TEXT("Behavior tree has not been set")))
		RunBehaviorTree(BehaviorTree);
}

void AEnemyAIController::OnTargetPerceptionUpdated(AActor* actor, FAIStimulus stimulus)
{
	const auto senseID = UAISense::GetSenseID<UAISense_Sight>();

	if (senseID == stimulus.Type && stimulus.WasSuccessfullySensed())
	{
		actor->Tags.Init({}, 1);
		actor->Tags[0] = "Spotted";
	}
}
