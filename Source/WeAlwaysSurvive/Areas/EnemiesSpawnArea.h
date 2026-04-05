// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemiesSpawnArea.generated.h"

UCLASS()
class WEALWAYSSURVIVE_API AEnemiesSpawnArea : public AActor
{
	GENERATED_BODY()

private:
	int32 EnemiesCount = 0;

	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY()
	class UActorDamageHandler* DamageHandler;

public:
	UPROPERTY(EditAnywhere)
	int32 EnemiesMaxCount = 10;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	float Rate = 2.f;
	
public:	
	// Sets default values for this actor's properties
	AEnemiesSpawnArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void StartSpawn();
	void StopSpawn();
	void SpawnEnemy();
	void OnSpawnedEnemyTakeDamage(AActor* damagedActor, AActor* damageCauser, float damage);
	void OnSpawnedEnemyDead(AActor* sender, float totalHealth, float totalExperience);
};
