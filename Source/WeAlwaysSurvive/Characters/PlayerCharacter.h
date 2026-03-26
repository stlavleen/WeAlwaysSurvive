// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeAlwaysSurvive/ExperienceReceiver.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class WEALWAYSSURVIVE_API APlayerCharacter : public ACharacter, public IExperienceReceiver
{
	GENERATED_BODY(EditAnywhere)

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	class UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAttackIndex;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Experience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> AttacksDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxExperience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> AttacksMaxDamage;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AddExperience(float value) override;

private:
	UFUNCTION()
	void TakeAnyDamage(AActor* damagedActor, float damage, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser);

	void RaiseTheLevel(float experience);
};
