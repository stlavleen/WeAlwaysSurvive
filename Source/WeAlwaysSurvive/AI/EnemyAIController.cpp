// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "WeAlwaysSurvive/Characters/PlayerCharacter.h"
#include "WeAlwaysSurvive/Characters/EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAIController::AEnemyAIController() : BehaviorTree(nullptr)
{
	auto senseConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseConfig_Sight"));
	senseConfig->SightRadius = 2000;
	senseConfig->LoseSightRadius = 2700;
	senseConfig->PeripheralVisionAngleDegrees = 90;
	senseConfig->DetectionByAffiliation.bDetectEnemies = true;
	senseConfig->DetectionByAffiliation.bDetectNeutrals = true;
	senseConfig->DetectionByAffiliation.bDetectFriendlies = true;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	PerceptionComponent->ConfigureSense(*senseConfig);
	PerceptionComponent->SetDominantSense(senseConfig->GetSenseImplementation());
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdate);
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
}

void AEnemyAIController::OnTargetPerceptionUpdate(AActor* actor, FAIStimulus stimulus)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, "OnTargetPerceptionUpdate is called");
	const auto senseID = UAISense::GetSenseID<UAISense_Sight>();
	auto playerCharacter = Cast<APlayerCharacter>(actor);

	if (senseID == stimulus.Type)
	{
		auto blackboardComp = GetBlackboardComponent();
		auto value = stimulus.WasSuccessfullySensed() && playerCharacter != nullptr ? playerCharacter : nullptr;
		blackboardComp->SetValueAsObject(PlayerActorKeyName, value);
	}
}
