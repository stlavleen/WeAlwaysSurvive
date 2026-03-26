// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMapLevelScriptActor.h"
#include "Kismet/GameplayStatics.h"
#include "ExperienceReceiver.h"


AActor* ABaseMapLevelScriptActor::FindExperienceReceiverByName(const FString& actorName)
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UExperienceReceiver::StaticClass(), actors);

	auto actor = actors.FindByPredicate([actorName](AActor* x) { return x->GetName().Equals(actorName); });

	return actor != nullptr? *actor : nullptr;
}

void ABaseMapLevelScriptActor::SendExperience(TMap<FString, int32> damageCausers, int32 totalExperience)
{
	AActor* actor = nullptr;
	
	for (const auto& pair : damageCausers) 
	{
		actor = FindExperienceReceiverByName(pair.Key);

		if (actor != nullptr) 
		{
			const auto totalHealth = 100.f; // TODO: get from parameter
			const auto experience = pair.Value / totalHealth * totalExperience;
			auto receiver = Cast<IExperienceReceiver>(actor);

			receiver->AddExperience(experience);
		}
	}
}
