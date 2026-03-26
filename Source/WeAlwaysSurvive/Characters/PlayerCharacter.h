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
	int32 AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAttackIndex;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Experience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> AttacksDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxExperience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> AttacksMaxDamage;

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

	virtual void AddExperience(int32 value) override;

private:
	UFUNCTION()
	void TakeAnyDamage(AActor* damagedActor, float damage, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser);

	void RaiseTheLevel(int32 experience);
};
