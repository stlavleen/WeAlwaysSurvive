// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

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

float AEnemyCharacter::GetHealth() const
{
	return Health;
}

float AEnemyCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

int32 AEnemyCharacter::GetLvl() const
{
	return Level;
}

bool AEnemyCharacter::GetIsDead() const
{
	return Health <= 0;
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

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (GetIsDead())
		DamageAmount = 0.0f;
	 
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
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
	Health = FMath::Clamp(Health - damage, 0, MaxHealth);

	OnTakeDamage.Broadcast(this, damageCauser, damage);

	if (GetIsDead()) 
		OnDeath.Broadcast(this, MaxHealth, OnDefeatExperience);
}

void AEnemyCharacter::SetDead()
{
	auto capsule = GetCapsuleComponent();
	capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(5.f);
}

