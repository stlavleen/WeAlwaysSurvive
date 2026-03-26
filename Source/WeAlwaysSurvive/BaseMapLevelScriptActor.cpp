// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMapLevelScriptActor.h"
#include "Kismet/GameplayStatics.h"
#include "ExperienceReceiver.h"

void ABaseMapLevelScriptActor::UpdateDamagedActors(FString damagedActor, FString damageCauser, int32 damage)
{
	if (DamagedActors.Contains(damagedActor)) 
	{
		UpdateDamageCausers(DamagedActors[damagedActor]->Map, damageCauser, damage);
	}
	else 
	{
		auto damageCausers = CreateDamageCausers(damageCauser, damage);
		DamagedActors.Add(damagedActor, damageCausers);
	}
}

void ABaseMapLevelScriptActor::HandleDeadActor(FString deadActor, float totalHealth, float totalExperience)
{
	if (!DamagedActors.Contains(deadActor))
		return;

	SendExperience(DamagedActors[deadActor]->Map, totalHealth, totalExperience);
	RemoveDamagedActor(deadActor);
}

UStringIntMapContainer* ABaseMapLevelScriptActor::CreateDamageCausers(FString damageCauser, int32 damage)
{
	auto damageCausers = NewObject<UStringIntMapContainer>();
	damageCausers->Map.Add(damageCauser, damage);

	return damageCausers;
}

void ABaseMapLevelScriptActor::UpdateDamageCausers(TMap<FString, int32>& damageCausers, FString damageCauser, int32 damage)
{
	auto existedDamageCauser = damageCausers.Find(damageCauser);

	if (damageCausers.Contains(damageCauser))
		damageCausers[damageCauser] += damage;
	else 
		damageCausers.Add(damageCauser, damage);
}

void ABaseMapLevelScriptActor::RemoveDamagedActor(FString damagedActor)
{
	if (DamagedActors.Contains(damagedActor))
	{
		auto damageCausers = DamagedActors[damagedActor];

		if (damageCausers != nullptr)
			damageCausers->ConditionalBeginDestroy();

		DamagedActors.Remove(damagedActor);
	}
}

void ABaseMapLevelScriptActor::SendExperience(TMap<FString, int32> damageCausers, float totalHealth, float totalExperience)
{
	AActor* actor = nullptr;

	for (const auto& pair : damageCausers)
	{
		actor = FindExperienceReceiverByName(pair.Key);

		if (actor != nullptr)
		{
			const auto experience = pair.Value / totalHealth * totalExperience;
			auto receiver = Cast<IExperienceReceiver>(actor);

			receiver->AddExperience(experience);
		}
	}
}

AActor* ABaseMapLevelScriptActor::FindExperienceReceiverByName(const FString& actorName)
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UExperienceReceiver::StaticClass(), actors);

	auto actor = actors.FindByPredicate([actorName](AActor* x) { return x->GetName().Equals(actorName); });

	return actor != nullptr ? *actor : nullptr;
}
