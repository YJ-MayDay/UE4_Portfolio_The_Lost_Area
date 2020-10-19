// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PlayerCharacter/StatusStruct.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "The_Lost_Area/The_Lost_AreaCharacter.h"
#include "The_Lost_Area/EnemyCharacter/AI_EnemyController.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"
#include "The_Lost_Area/The_Lost_AreaCharacter.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "The_Lost_Area/EnemyCharacter/EnemyAnimInstance.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "The_Lost_Area/PlayGameMode/PlayGameMode.h"

//�÷��̾ ������ �� �ְ� �� ĳ������ �����ڿ��� ���� �ڽ� �ݶ��̴��� ����,
//BeginPlay ���� ��տ� �ٿ��־����ϴ�.
AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	LHandCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LHandCollision"));
	LHandCollision->SetupAttachment(GetMesh());

	RHandCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RHandCollision"));
	RHandCollision->SetupAttachment(GetMesh());

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AThe_Lost_AreaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Anim = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());

	NowState = ENowState::Move;
	status.HealthPoint = 100;
	status.AttackDamage = 2;

	LHandCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "middle_01_l");
	RHandCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "middle_01_r");

	LHandCollision->SetRelativeScale3D(FVector(0.2f, 0.1f, 0.2f));
	RHandCollision->SetRelativeScale3D(FVector(0.2f, 0.1f, 0.2f));

	LHandCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlapBegin);
	RHandCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlapBegin);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DetectedDistance = GetDistanceTo(Player);
	UE_LOG(LogTemp, Warning, TEXT("DetectedDistance :: %f"), DetectedDistance);
	if (!isDeath)
	{
		if (status.HealthPoint <= 0)
		{
			NowState = ENowState::Death;
			isDeath = true;
		}
		else if (DetectedDistance < AttackRange)
		{
			NowState = ENowState::Attack;
		}
		else if(DetectedDistance > AttackRange)
		{
			NowState = ENowState::Move;
		}
	}

	if (isFire)
	{
		ContinuingFire(DeltaTime);
	}
}

void AEnemyCharacter::ContinuingFire(float DeltaTime)
{
	DuringFire += DeltaTime;

	if (DuringFire >= 0.5f)
	{
		status.HealthPoint -= 10;
		DuringFire = 0;

		FiringCheck++;
	}

	if (FiringCheck >= 5)
	{
		isFire = false;
	}
}

//�� ĳ���͸� �ٽ� ������ �� �ʿ��� ���� �Դϴ�.
void AEnemyCharacter::SetActivateEnemy()
{
	Anim->SetActivate(true);

	NowState = ENowState::Move;
	isDeath = false;
	
	SetRespawnStatus();

	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
	SetActorHiddenInGame(false);

	GetCharacterMovement()->Activate();
}

//������ �� �⺻���� ü���� �������ָ�, 
//�������� ������ ���� ���̵��� ������� �������� ���� �߰������� ü�°� ���ݷ�, ������ ���� �� �־����ϴ�.
void AEnemyCharacter::SetRespawnStatus()
{
	status.HealthPoint = 100;
	APlayGameMode* GameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode->GetStageCount() != 1)
	{
		status.HealthPoint = status.HealthPoint + (IncreaseHealthPoint * (GameMode->GetStageCount() - 1));
		status.DefensePoint = status.DefensePoint + IncreaseHealthDefense;
		status.AttackDamage = status.AttackDamage + IncreaseHealthDamage;
	}
	status.MaxHealthPoint = status.HealthPoint;
}

ENowState AEnemyCharacter::SetNowState(ENowState State)
{
	return NowState = State;
}

void AEnemyCharacter::SetDamage(int32 Damage)
{
	status.HealthPoint -= Damage;
}

bool AEnemyCharacter::SetIsFire(bool bisFire)
{
	return isFire = bisFire;
}

bool AEnemyCharacter::SetIsBomb(bool bisBomb)
{
	return isBomb = bisBomb;
}

bool AEnemyCharacter::SetbIsAttacking(bool bValue)
{
	return IsAttacking = bValue;
}

//�� ĳ���Ϳ��� ������ �ξ��� �ڽ� �ݶ��̴��� �÷��̾�� �ε����� ���� Ž���ϴ� �Լ��Դϴ�.
//���� �ڽ� �ݶ��̴��� �÷��̾��� ĸ�� �ݶ��̴��� �浹�ϸ� �÷��̾��� ü���� �ٿ��ݴϴ�.
void AEnemyCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		AThe_Lost_AreaCharacter* player = Cast<AThe_Lost_AreaCharacter>(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Name :: %s"), *player->GetName());

		player->SetHealthPoint(status.AttackDamage);
	}
}



