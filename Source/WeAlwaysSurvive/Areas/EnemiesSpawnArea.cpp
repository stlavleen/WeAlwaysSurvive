// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesSpawnArea.h"
#include "WeAlwaysSurvive/Characters/EnemyCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemiesSpawnArea::AEnemiesSpawnArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);
	EnemiesCount = 0;
	EnemiesMaxCount = 10;
	Rate = 2.f;
}

// Called when the game starts or when spawned
void AEnemiesSpawnArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemiesSpawnArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemiesSpawnArea::DecreaseEnemiesCount()
{
	EnemiesCount--;
}

void AEnemiesSpawnArea::StartSpawn()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemiesSpawnArea::SpawnEnemy, Rate, true);
}

void AEnemiesSpawnArea::StopSpawn()
{
	if (TimerHandle.IsValid())
		GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AEnemiesSpawnArea::SpawnEnemy()
{
	if (EnemiesCount >= EnemiesMaxCount)
	{
		StopSpawn();
		return;
	}

	const auto origin = Box->Bounds.Origin;
	const auto originalExtent = Box->Bounds.BoxExtent;
	const auto extent = FVector(originalExtent.X, originalExtent.Y, 0);
	const auto location = UKismetMathLibrary::RandomPointInBoundingBox(origin, extent);
	const auto rotation = FRotator(0.f, 0.f, FMath::RandRange(0.f, 360.f));

	auto enemy = GetWorld()->SpawnActor<AEnemyCharacter>(*EnemyClass, location, rotation);

	if (enemy == nullptr)
	{
		StopSpawn();
		return;
	}

	enemy->OnTakeDamage.AddDynamic(this, &AEnemiesSpawnArea::OnSpawnedEnemyTakeDamage);
	enemy->OnDeath.AddDynamic(this, &AEnemiesSpawnArea::OnSpawnedEnemyDead);

	EnemiesCount++;
}

