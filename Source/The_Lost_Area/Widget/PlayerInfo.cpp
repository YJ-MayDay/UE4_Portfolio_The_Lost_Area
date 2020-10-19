// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInfo.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "The_Lost_AreaCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "The_Lost_Area/EnemyCharacter/EnemyCharacter.h"
#include "The_Lost_Area/PlayGameMode/PlayGameMode.h"

void UPlayerInfo::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Player = Cast<AThe_Lost_AreaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Casting is Nullptr"));
		return;
	}

	BloodImage->SetRenderOpacity(0.0f);

	for (int32 i = 0; i < Player->Inventory.Num(); i++)
	{
		if (Player->Inventory[i].Kinds != EItemKinds::Equipment)
			ShowItem.Add(Player->Inventory[i]);
	}
}


void UPlayerInfo::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	//���� ���°� �ƴ� ��, (Press Enter Key) �� ���̵���/�ƿ��� �ݺ��ϸ� ǥ�� 
	if (!Player->GetIsEnemySpawn())
	{
		Press->SetVisibility(ESlateVisibility::Visible);

		if (opacity > 0.99f)
			DeltaValue = DeltaValue * -1;
		else if (opacity < 0.0f)
			DeltaValue = DeltaValue * -1;

		opacity = opacity + DeltaValue;

		Press->SetOpacity(opacity);
	}
	else
		Press->SetVisibility(ESlateVisibility::Collapsed);
}

//�÷��̾�� �Ѱ��� ���� ������ ������ �޾� ȭ�鿡 ������ �������� �����մϴ�.
void UPlayerInfo::SetShowItemCount(struct FInventoryList Inven)
{
	ShowIcon->SetBrushFromSoftTexture(Inven.Icon);
	ShowCount->SetText(FText::AsNumber(Inven.ItemCount));
}

void UPlayerInfo::SetAmmoCount(int32 AmmoCount)
{
	CurrentAmmoCount->SetText(FText::FromString(FString::FromInt(AmmoCount)));
}

void UPlayerInfo::SetTotalAmmoCount(int32 totalCount)
{
	TotalAmmoCount->SetText(FText::FromString(FString::FromInt(totalCount)));
}

void UPlayerInfo::SetOpacity(int32 FadeValue)
{
	float PercentHP = (100.f - static_cast<float>(FadeValue)) / 200;
	BloodImage->SetRenderOpacity(PercentHP);
}

//PlayerInfo UI �� �ʿ��� �������� ������ �ݴϴ�.
//���ھ� / �������� ī���� / �÷��̾� ü�� / �� ī��Ʈ ���
void UPlayerInfo::SetScore(int32 ScoreValue)
{
	Score->SetText(FText::AsNumber(ScoreValue));

	APlayGameMode* GameMode = Cast<APlayGameMode>(GetWorld()->GetAuthGameMode());
	RoundCount->SetText(FText::AsNumber(GameMode->GetStageCount()));

	PlayerHP->SetText(FText::AsNumber(Player->status.HealthPoint));
	Damage->SetText(FText::AsNumber(Player->status.AttackDamage));
	TArray<AActor*> TempEnemy;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), TempEnemy);
	
	if (TempEnemy.Num() != 0)
	{
		int32 LiveEnemyCount = 0;
		for (int32 i = 0; i < TempEnemy.Num(); i++)
		{
			if (TempEnemy[i]->bHidden == false)
				LiveEnemyCount++;
		}
		EnemyCount->SetText(FText::AsNumber(LiveEnemyCount));
	}
	else 
		EnemyCount->SetText(FText::AsNumber(0));
}

void UPlayerInfo::SetDefenseCount(int32 DefenseValue)
{
	DefenseCount->SetText(FText::AsNumber(DefenseValue));
}

