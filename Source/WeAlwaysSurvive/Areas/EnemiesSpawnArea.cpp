// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesSpawnArea.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WeAlwaysSurvive/Handlers/ActorDamageHandler.h"

// Sets default values
AEnemiesSpawnArea::AEnemiesSpawnArea() : DamageHandler(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetCollisionProfileName(FName(TEXT("NoCollision")));
	Box->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemiesSpawnArea::BeginPlay()
{
	Super::BeginPlay();

	DamageHandler = NewObject<UActorDamageHandler>(this);

	StartSpawn();
}

// Called every frame
void AEnemiesSpawnArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemiesSpawnArea::SpawnedEnemyTakeDamage(AActor* damagedActor, AActor* damageCauser, float damage)
{
	const auto damagedActorName = UKismetSystemLibrary::GetObjectName(damagedActor);
	const auto damageCauserName = UKismetSystemLibrary::GetObjectName(damageCauser);
	DamageHandler->UpdateDamagedActors(damagedActorName, damageCauserName, damage);
}

void AEnemiesSpawnArea::SpawnedEnemyDead(AActor* sender, float totalHealth, float totalExperience)
{
	const auto senderName = UKismetSystemLibrary::GetObjectName(sender);
	DamageHandler->HandleDeadActor(senderName, totalHealth, totalExperience);
	LiveEnemiesCount--;
	OnSpawnedEnemyDeath.Broadcast(sender, totalHealth, totalExperience);
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
	if (LiveEnemiesCount >= EnemiesMaxCount) 
	{
		StopSpawn();
		return;
	}	

	const auto origin = Box->Bounds.Origin;
	const auto originalExtent = Box->Bounds.BoxExtent;
	const auto extent = FVector(originalExtent.X, originalExtent.Y, 0);
	const auto location = UKismetMathLibrary::RandomPointInBoundingBox(origin, extent);
	const auto rotation = FRotator(0.f, FMath::RandRange(0.f, 360.f), 0.f);

	auto enemy = GetWorld()->SpawnActor<AEnemyCharacter>(*EnemyClass, location, rotation);

	if (enemy == nullptr)
		return;

	enemy->OnTakeDamage.AddDynamic(this, &AEnemiesSpawnArea::SpawnedEnemyTakeDamage);
	enemy->OnDeath.AddDynamic(this, &AEnemiesSpawnArea::SpawnedEnemyDead);
	enemy->SpawnDefaultController();

	LiveEnemiesCount++;
}

