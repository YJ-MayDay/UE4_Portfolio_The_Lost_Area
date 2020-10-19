// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "EnemyCharacter.h"

void UEnemyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	OwnerChar = Cast<AEnemyCharacter>(TryGetPawnOwner());

	if (OwnerChar == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OwnerChar Cast Failed "));
		return;
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerChar != nullptr)
	{
		switch (OwnerChar->GetNowState())
		{
		case ENowState::Move:
			isMove = true;
			isAttack = false;
			break;

		case ENowState::Attack:
			isAttack = true;
			isMove = false;
			break;
		}
	}
}

bool UEnemyAnimInstance::SetActivate(bool value)
{
	return isActivate = value;
}
