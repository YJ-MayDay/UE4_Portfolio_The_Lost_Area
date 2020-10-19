// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter/StatusStruct.h"
#include "EnemyCharacter.generated.h"

UENUM(BlueprintType)
enum class ENowState : uint8
{
	Move,
	Attack,
	Death
};

UCLASS()
class THE_LOST_AREA_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	AEnemyCharacter();

public:	
	virtual void Tick(float DeltaTime) override;

	ENowState GetNowState() { return NowState; }
	ENowState SetNowState(ENowState State);

	float GetAttackRange() { return AttackRange; }

	UFUNCTION()
		void SetDamage(int32 Damage);

	void SetActivateEnemy();

	bool SetIsFire(bool bisFire);
	bool SetIsBomb(bool bisBomb);

	bool GetbIsAttacking() { return IsAttacking; }
	bool SetbIsAttacking(bool bValue);
 
	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* AttackMontage;
	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* KnockBackMontage;

protected:

	virtual void BeginPlay() override;

	UPROPERTY()
		class AThe_Lost_AreaCharacter* Player;

	UPROPERTY()
		class UEnemyAnimInstance* Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		struct FEnemyStatusStruct status;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent* LHandCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent* RHandCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<class UMaterialInstance*> arrMaterial;
	
	UPROPERTY(VisibleAnywhere)
		ENowState NowState;


	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetRespawnStatus();
	
	UPROPERTY(EditDefaultsOnly)
		float DetectedDistance = 0.f;

	UPROPERTY(EditDefaultsOnly)
		float AttackRange = 200.0f;

	void ContinuingFire(float DeltaTime);

	bool isDeath = false;
	bool isFire = false;
	bool isBomb = false;

	int32 FiringCheck = 0;
	float DuringFire = 0.0f;

	bool IsAttacking = false;
	const int32 IncreaseHealthPoint = 10;
	const int32 IncreaseHealthDefense = 1;
	const int32 IncreaseHealthDamage = 2;
};
