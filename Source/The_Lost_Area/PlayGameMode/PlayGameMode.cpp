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

//적을 필드에 스폰해주는 함수입니다.
//미리 리스폰스팟을 설정, 적 캐릭터를 오브젝트 풀링으로 미리 선언 후,
//난수를 생성해 랜덤한 리스폰 스팟위치에 적 캐릭터를 리스폰 시켜줍니다.
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

	//기본 오브젝트 풀링은 100개를 만들었지만 게임이 진행되며 스폰되어야 할 적이 
	//100 이상이 될 경우 추가적으로 100개씩 풀링을 추가로 진행합니다.
	if (Enemy.Num() / Player->GetEnemyCount() == StageCount)
	{
		ObjectPooling();
	}
}

//필드에 있는 적의 상태를 검사하는 함수입니다.
void APlayGameMode::CheckEnemy()
{
	if (Enemy.IsValidIndex(SpawnEnemyCount))
	{
		int32 DeathCheckCount = 0;
		DeathCheck(DeathCheckCount);
	}
}

//스폰된 적 캐릭터를 재귀함수로 돌며 현재 상태를 검사합니다.
//스폰되어 있는 모든 적이 사망상태가 되었을 때, 
//스폰 함수를 종료하며 다음 스테이지로 넘어가기 위해 각 변수를 초기화 해주고 스테이지 카운터를 중가시켜줍니다.
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

//처음 BeginPlay가 시작 될 때, 기본적으로 적 캐릭터를 100개 생성 후 TArray Enemy 변수에 추가해 가지고 있습니다.
//다만 게임 플레이시에 방해되지 않게 비활성화 시에는 보이지 않게 설정하였습니다.
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

//필드 상에 배치해 놓은 리스폰 스팟을 코드에서 불러들여 하나로 관리하기 위해 TArray RespawnSpot 변수에 가지고 있습니다.
void APlayGameMode::SetRespawnSpot()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGM_RespawnSpot::StaticClass(), RespawnSpots);
}