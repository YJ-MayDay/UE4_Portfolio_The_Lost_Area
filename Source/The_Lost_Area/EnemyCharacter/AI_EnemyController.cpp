// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_EnemyController.h"
#include "The_Lost_Area/The_Lost_AreaCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "EnemyCharacter.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "The_Lost_Area/EnemyCharacter/EnemyAnimInstance.h"
#include "The_Lost_Area/EndGameMode/GameDataInstance.h"

void AAI_EnemyController::BeginPlay()
{
	Super::BeginPlay();

	TempChar = Cast<AEnemyCharacter>(AAIController::K2_GetPawn());

	Player = Cast<AThe_Lost_AreaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AAI_EnemyController::Tick(float DeltaSecends)
{
	Super::Tick(DeltaSecends);

	if (TempChar == nullptr)
	{
		TempChar = Cast<AEnemyCharacter>(AAIController::K2_GetPawn());
		Anim = Cast<UEnemyAnimInstance>(TempChar->GetMesh()->GetAnimInstance());
	}
	
	//적의 현재 상태 별로 다른 액션을 주었으며,
	//Move 일 때는 플레이어에게 이동 / Attack 일 때는 공격 / Death 일 때는 플레이어에게 보상을 주고,
	//각 기능들을 꺼주며 움직일 수 없는 상태로 만들어 줍니다.
	switch (TempChar->GetNowState())
	{
	case ENowState::Move:
		IsAttack = false;
		if (TempChar->GetDistanceTo(Player) > TempChar->GetAttackRange() && Anim->GetActivate())
		{
			MoveToActor(Player, 50.0f);
		}
		break;
	case ENowState::Attack:
		IsAttack = true;

		if (!Anim->IsAnyMontagePlaying() && !IsDeath)
			Anim->Montage_Play(TempChar->AttackMontage, 1.0f);
		break;
	case ENowState::Death:
			TempChar->GetCharacterMovement()->Deactivate();
			UE_LOG(LogTemp, Warning, TEXT("Enemy State Death"));
		if (Anim->GetActivate())
		{
			IsDeath = true;

			if (!IsReward)
			{
				IsReward = true;
				Player->status.Score += 150;
			}

			TempChar->SetActorEnableCollision(false);
			TempChar->SetActorTickEnabled(false);

			DeathTime += DeltaSecends;
			if (DeathTime >= 3.0f)
			{
				UGameDataInstance* Instance = Cast<UGameDataInstance>(GetWorld()->GetGameInstance());
				Instance->SetKills();

				TempChar->SetActorHiddenInGame(true);

				Anim->SetActivate(false);

				IsDeath = false;
				IsReward = false;
				DeathTime = 0;

			}
		}
		break;
	}
}
