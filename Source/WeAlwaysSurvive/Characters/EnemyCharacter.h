// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeAlwaysSurvive/Objects/StatsObject.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class WEALWAYSSURVIVE_API AEnemyCharacter : public ACharacter, public IStatsObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> AttacksDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> AttacksMaxDamage;

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	virtual int32 GetHealth() const override;
	
	UFUNCTION(BlueprintCallable)
	virtual int32 GetMaxHealth() const override;

	UFUNCTION(BlueprintCallable)
	virtual int32 GetLvl() const override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	bool Attack(AActor* actor, int32 damageIndex);

private:
	UFUNCTION()
	void TakeAnyDamage(AActor* damagedActor, float damage, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser);
};
