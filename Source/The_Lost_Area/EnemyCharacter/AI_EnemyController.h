// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class THE_LOST_AREA_API AAI_EnemyController : public AAIController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSecends) override;

	class AThe_Lost_AreaCharacter* Player;
	
	class AEnemyCharacter* TempChar;
	class UEnemyAnimInstance* Anim;

	UPROPERTY(BlueprintReadWrite)
	bool IsAttack = false;

	UPROPERTY(BlueprintReadWrite)
		bool IsDeath = false;

	UPROPERTY(BlueprintReadWrite)
		bool IsReward = false;

	float DeathTime = 0.0f;
};
