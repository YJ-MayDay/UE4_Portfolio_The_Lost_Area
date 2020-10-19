// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBuyUI.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "The_Lost_Area/The_Lost_AreaCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// 버튼 이미지는 수정해야 됨

void UAmmoBuyUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Player = Cast<AThe_Lost_AreaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Cash->SetText(FText::AsNumber(Player->status.Score));

	if (Bullet556 != nullptr)
		Bullet556->OnClicked.AddDynamic(this, &UAmmoBuyUI::BuyBullet556);

	if (Bullet762 != nullptr)
		Bullet762->OnClicked.AddDynamic(this, &UAmmoBuyUI::BuyBullet762);

	if (HPup != nullptr)
		HPup->OnClicked.AddDynamic(this, &UAmmoBuyUI::BuyHPup);

	if (DamageUP != nullptr)
		DamageUP->OnClicked.AddDynamic(this, &UAmmoBuyUI::BuyDamageUP);

	if (BulletUP != nullptr)
		BulletUP->OnClicked.AddDynamic(this, &UAmmoBuyUI::BuyMaxBulletUP);

	Bullet556_Price = Bullet762_Price = 200;
	HPup_Price = 1000;
	Damage_Price = 500;
	Bullet_Price = 500;
}

void UAmmoBuyUI::SetScore(int32 ScoreValue)
{
	Cash->SetText(FText::AsNumber(ScoreValue));
}

void UAmmoBuyUI::BuyBullet556()
{
	if (0 <= Player->status.Score - Bullet556_Price)
	{
		Player->status.Score -= Bullet556_Price;

		Player->Total556Bullet += 30;
		SetScore(Player->status.Score);

		//UE_LOG(LogTemp, Warning, TEXT("BuyBullet556"));
	}
}

void UAmmoBuyUI::BuyBullet762()
{
	if (0 <= Player->status.Score - Bullet762_Price)
	{
		Player->status.Score -= Bullet762_Price;

		Player->Total762Bullet += 30;
		SetScore(Player->status.Score);

		//UE_LOG(LogTemp, Warning, TEXT("BuyBullet762"));
	}
}

void UAmmoBuyUI::BuyHPup()
{
	if (0 <= Player->status.Score - HPup_Price)
	{
		Player->status.Score -= HPup_Price;

		Player->status.MaxHealthPoint += 10;
		SetScore(Player->status.Score);

		//UE_LOG(LogTemp, Warning, TEXT("BuyHPup"));
	}
}

void UAmmoBuyUI::BuyDamageUP()
{
	if (0 <= Player->status.Score - Damage_Price)
	{
		Player->status.Score -= Damage_Price;

		Player->status.AttackDamage += 2;
		SetScore(Player->status.Score);

		//UE_LOG(LogTemp, Warning, TEXT("BuyDamageUP"));
	}
}

void UAmmoBuyUI::BuyMaxBulletUP()
{
	if (0 <= Player->status.Score - Bullet_Price)
	{
		Player->status.Score -= Bullet_Price;

		Player->CarryFullBullet += 10;
		SetScore(Player->status.Score);

		//UE_LOG(LogTemp, Warning, TEXT("BuyMaxBulletUP"));
	}
}
