// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THE_LOST_AREA_API APlayGameMode : public AGameModeBase
{
	GENERATED_BODY()

		APlayGameMode();

public:

	void SpawnEnemy();
	int32 GetStageCount() { return StageCount; }

	void SetRespawnSpot();
	void ObjectPooling();

private:

	class AThe_Lost_AreaCharacter* Player;

	TArray<class AEnemyCharacter*> TempEnemyChar;

	bool isAllDeath = false;

	void DeathCheck(int32 DeathCheckCount);

	int32 SpawnEnemyCount = 0;
	int32 ActivateEnemyCheck = 0;

	int32 StageCount = 1;

	UPROPERTY()
		FTimerHandle timer;

	class AEnemyCharacter* TestEnemy;

	TArray<class AEnemyCharacter*> Enemy;
	TArray<bool> EnemyStateCheck;
	void CheckEnemy();
	int32 Checkint = 0;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSecends) override;

	TArray<AActor*> RespawnSpots;

	bool SpawnStart = false;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemyCharacter> EnemyChar;

	class AEnemyCharacter* TempEnemyChar2;

	bool isCheckSpawn = false;

	//void SetRespawnSpot();

	float TestTick = 0;
	float SpawnTime = 10.f;
};
