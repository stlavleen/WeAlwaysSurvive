// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/CollisionProfile.h"
#include "Engine/DamageEvents.h"
#include "EnemyCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	Health = 100;
	Stamina = 100;
	Experience = 0;
	Level = 1;
	AttacksDamage = {};
	MaxHealth = 100;
	MaxStamina = 100;
	MaxExperience = 100;
	MaxLevel = 85;
	AttacksMaxDamage = {};
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	OnTakeAnyDamage.AddDynamic(this, &APlayerCharacter::TakeAnyDamage);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::TakeAnyDamage(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigatedBy, AActor* damageCauser)
{
	Health = FMath::Clamp(Health - StaticCast<int32>(damage), 0, MaxHealth);
}

void APlayerCharacter::ApplyAttack()
{
	auto world = GetWorld();
	const auto start = GetActorLocation();
	const auto end = GetActorForwardVector() * AttackDistance + start;
	ETraceTypeQuery channel = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility);
	const bool traceComplex = false;
	const TArray<AActor*> actorsToIgnore = {};
	const auto drawDebugType = EDrawDebugTrace::ForDuration;
	FHitResult hitResult;
	bool ignoreSelf = true;
	
	const auto value = UKismetSystemLibrary::LineTraceSingle(
		world, start, end, channel, traceComplex, actorsToIgnore, drawDebugType, hitResult, ignoreSelf);

	if (!value)
		return;

	auto enemyCharacter = Cast<AEnemyCharacter>(hitResult.GetActor());

	if (enemyCharacter == nullptr)
		return;

	if (!AttacksDamage.IsValidIndex(CurrentAttackIndex))
		return;

	auto damage = AttacksDamage[CurrentAttackIndex];
	FDamageEvent damageEvent{};

	const auto actualDamage = enemyCharacter->TakeDamage(damage, damageEvent, nullptr, nullptr);

	if (actualDamage > 0 && enemyCharacter->GetIsDead())
		Experience += 30; // TODO: move to config
}


