// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Engine/DamageEvents.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	Health = 100;
	Level = 1;
	AttacksDamage = {};
	MaxHealth = 100;
	MaxLevel = 85;
	AttacksMaxDamage = {};
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OnTakeAnyDamage.AddDynamic(this, &AEnemyCharacter::TakeAnyDamage);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

int32 AEnemyCharacter::GetHealth() const
{
	return Health;
}

int32 AEnemyCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

int32 AEnemyCharacter::GetLvl() const
{
	return Level;
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AEnemyCharacter::Attack(AActor* actor, int32 damageIndex)
{
	if (!AttacksDamage.IsValidIndex(damageIndex))
		return false;

	const auto damageEvent = FDamageEvent();
	actor->TakeDamage(AttacksDamage[damageIndex], damageEvent, nullptr, nullptr);

	return true;
}

void AEnemyCharacter::TakeAnyDamage(AActor* damagedActor, float damage, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser) 
{
	Health = FMath::Clamp(Health - StaticCast<int32>(damage), 0, MaxHealth);
}

