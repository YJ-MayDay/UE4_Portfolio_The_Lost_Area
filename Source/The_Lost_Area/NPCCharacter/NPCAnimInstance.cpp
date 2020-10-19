// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAnimInstance.h"
#include "NPCCharacter/NPCCharacter.h"
#include "The_Lost_Area/The_Lost_AreaCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
void UNPCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwnerChar == nullptr || Player == nullptr)
		return;

	Distance = Player->GetDistanceTo(OwnerChar);
	UIPopup = OwnerChar->GetIsPopup();

}

//�÷��̾��� �ൿ�̳� �Ÿ��� ���� �ִϸ��̼��� ���ݾ� ���� �ֱ� ����,
//�Ÿ��� üũ�� �� �������Ʈ�� �Ѱ��ݴϴ�.
void UNPCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerChar = Cast<ANPCCharacter>(TryGetPawnOwner());

	Player = Cast<AThe_Lost_AreaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (OwnerChar == nullptr || Player == nullptr) return;

	InterectionCheck = Player->InteractionRange;
}
