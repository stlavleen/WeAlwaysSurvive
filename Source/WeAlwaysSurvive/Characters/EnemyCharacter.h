// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeAlwaysSurvive/Objects/StatsObject.h"
#include "EnemyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTakeDamageSignature, AActor*, damagedActor,  AActor*, damageCauser, float, damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDeathEventSignature, AActor*, sender, float, totalHealth, float, totalExperience);

UCLASS()
class WEALWAYSSURVIVE_API AEnemyCharacter : public ACharacter, public IStatsObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> AttacksDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> AttacksMaxDamage;

	UPROPERTY(EditAnywhere)
	float OnDefeatExperience = 30;

public:
	UPROPERTY(BlueprintAssignable)
	FOnTakeDamageSignature OnTakeDamage;
	
	UPROPERTY(BlueprintAssignable)
	FOnDeathEventSignature OnDeath;

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	virtual float GetHealth() const override;
	
	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHealth() const override;

	UFUNCTION(BlueprintCallable)
	virtual int32 GetLvl() const override;

	UFUNCTION(BlueprintCallable)
	bool GetIsDead() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	bool Attack(AActor* actor, int32 damageIndex);

private:
	UFUNCTION()
	void TakeAnyDamage(AActor* damagedActor, float damage, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser);
};
