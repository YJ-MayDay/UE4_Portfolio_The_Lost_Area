// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "The_Lost_Area/GM_RespawnSpot.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "The_Lost_Area/EnemyCharacter/EnemyCharacter.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "The_Lost_Area/The_Lost_AreaCharacter.h"

#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include"Runtime/Engine/Classes/Animation/AnimInstance.h"
APlayGameMode::APlayGameMode()
{
	PrimaryActorTick.bCanEverTick = true; 

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;

		UE_LOG(LogTemp, Warning, TEXT("%s"), *DefaultPlayerName.ToString());
	}
}

//���� �ʵ忡 �������ִ� �Լ��Դϴ�.
//�̸� ������������ ����, �� ĳ���͸� ������Ʈ Ǯ������ �̸� ���� ��,
//������ ������ ������ ������ ������ġ�� �� ĳ���͸� ������ �����ݴϴ�.
void APlayGameMode::SpawnEnemy()
{

	if (RespawnSpots.Num() != 0 && Enemy.Num() != 0)
	{
		if (SpawnEnemyCount < (Player->GetEnemyCount() * StageCount))
		{
			Enemy[SpawnEnemyCount]->SetNowState(ENowState::Move);
			int32 Random = FMath::RandRange(0, RespawnSpots.Num() - 1);

			Enemy[SpawnEnemyCount]->SetActorLocation(RespawnSpots[Random]->GetActorLocation());
			Enemy[SpawnEnemyCount]->SetActivateEnemy();
			
			SpawnEnemyCount++;
			GetWorld()->GetTimerManager().SetTimer(timer, this, &APlayGameMode::SpawnEnemy, 0.5f);
		}
	}

	//�⺻ ������Ʈ Ǯ���� 100���� ��������� ������ ����Ǹ� �����Ǿ�� �� ���� 
	//100 �̻��� �� ��� �߰������� 100���� Ǯ���� �߰��� �����մϴ�.
	if (Enemy.Num() / Player->GetEnemyCount() == StageCount)
	{
		ObjectPooling();
	}
}

//�ʵ忡 �ִ� ���� ���¸� �˻��ϴ� �Լ��Դϴ�.
void APlayGameMode::CheckEnemy()
{
	if (Enemy.IsValidIndex(SpawnEnemyCount))
	{
		int32 DeathCheckCount = 0;
		DeathCheck(DeathCheckCount);
	}
}

//������ �� ĳ���͸� ����Լ��� ���� ���� ���¸� �˻��մϴ�.
//�����Ǿ� �ִ� ��� ���� ������°� �Ǿ��� ��, 
//���� �Լ��� �����ϸ� ���� ���������� �Ѿ�� ���� �� ������ �ʱ�ȭ ���ְ� �������� ī���͸� �߰������ݴϴ�.
void APlayGameMode::DeathCheck(int32 DeathCheckCount)
{
	if (DeathCheckCount < SpawnEnemyCount && Enemy[DeathCheckCount]->GetNowState() == ENowState::Death)
	{
		DeathCheckCount++;
		DeathCheck(DeathCheckCount);
		
		if (DeathCheckCount == SpawnEnemyCount && Enemy[SpawnEnemyCount - 1]->GetNowState() == ENowState::Death)
		{
			SpawnEnemyCount = 0;
			ActivateEnemyCheck = 0;
			Player->SetIsEnemySpawn(false);
			StageCount++;
			UE_LOG(LogTemp, Warning, TEXT("IsSpawning End"));
		}
	}

}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AThe_Lost_AreaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SetRespawnSpot();

	ObjectPooling();
}

//ó�� BeginPlay�� ���� �� ��, �⺻������ �� ĳ���͸� 100�� ���� �� TArray Enemy ������ �߰��� ������ �ֽ��ϴ�.
//�ٸ� ���� �÷��̽ÿ� ���ص��� �ʰ� ��Ȱ��ȭ �ÿ��� ������ �ʰ� �����Ͽ����ϴ�.
void APlayGameMode::ObjectPooling()
{

	for (int32 i = 0; i < 100; i++)
	{

		FActorSpawnParameters SpawnParam;

		AEnemyCharacter* TempEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyChar, SpawnParam);
	
		TempEnemy->SetActorEnableCollision(false);
		TempEnemy->SetActorTickEnabled(false);
		TempEnemy->SetActorHiddenInGame(true);

		Enemy.Add(TempEnemy);

	}

	UE_LOG(LogTemp, Warning, TEXT("Enemy Num :: %d"), Enemy.Num());
	
}

void APlayGameMode::Tick(float DeltaSecends)
{
	Super::Tick(DeltaSecends);

	CheckEnemy();
}

//�ʵ� �� ��ġ�� ���� ������ ������ �ڵ忡�� �ҷ��鿩 �ϳ��� �����ϱ� ���� TArray RespawnSpot ������ ������ �ֽ��ϴ�.
void APlayGameMode::SetRespawnSpot()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGM_RespawnSpot::StaticClass(), RespawnSpots);
}