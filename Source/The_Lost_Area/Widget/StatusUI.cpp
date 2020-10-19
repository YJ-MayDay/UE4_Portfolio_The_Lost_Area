// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusUI.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "The_Lost_Area/The_Lost_AreaCharacter.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"


void UStatusUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	player = Cast<AThe_Lost_AreaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	HealthCount = BulletCount = StaminaCount = 0;

	if (Health_L != nullptr)
		Health_L->OnClicked.AddDynamic(this, &UStatusUI::Health_DecreaseValue);

	if (Health_R != nullptr)
		Health_R->OnClicked.AddDynamic(this, &UStatusUI::Health_IncreaseValue);

	if (Bullet_L != nullptr)
		Bullet_L->OnClicked.AddDynamic(this, &UStatusUI::Bullet_DecreaseValue);

	if (Bullet_R != nullptr)
		Bullet_R->OnClicked.AddDynamic(this, &UStatusUI::Bullet_IncreaseValue);

	if (Stamina_L != nullptr)
		Stamina_L->OnClicked.AddDynamic(this, &UStatusUI::Stamina_DecreaseValue);

	if (Stamina_R != nullptr)
		Stamina_R->OnClicked.AddDynamic(this, &UStatusUI::Stamina_IncreaseValue);
	
	TArray<AActor*> arrActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AThe_Lost_AreaCharacter::StaticClass(), arrActor);
	if (arrActor.Num() == 1)
	{
		AThe_Lost_AreaCharacter* Player = Cast< AThe_Lost_AreaCharacter>(arrActor[0]);
		UE_LOG(LogTemp, Warning, TEXT("arrActor is 1 "));

		//TotalStatusCount = Player->GetStatusCount();
		SetChangeUpText(TotalStatusCount);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("arrActor is 1 Over, Check Please"));
}


void UStatusUI::SetChangeUpText(int TotalCount)
{
	FString strTemp = FString::FromInt(TotalCount);
	FText temp = FText::FromString(strTemp);
	StatusCount->SetText(temp);
}

void UStatusUI::Health_IncreaseValue()
{
	/*if (HealthCount < 0.99f && player->status.StatusCount != 0)
	{
		HealthCount += 0.05f;
		HealthScroll->SetPercent(HealthCount);

		player->status.StatusCount--;
		SetStatusCount(player->status.StatusCount);
	}
		UE_LOG(LogTemp, Warning, TEXT("HPCount :; %f"), HealthCount);
		UE_LOG(LogTemp, Warning, TEXT("Status Count :; %d"), player->status.StatusCount);*/
}

void UStatusUI::Health_DecreaseValue()
{
	/*if (HealthCount > 0.01f)
	{
		HealthCount -= 0.05f;
		HealthScroll->SetPercent(HealthCount);

		player->status.StatusCount++;
		SetStatusCount(player->status.StatusCount);
	}
	UE_LOG(LogTemp, Warning, TEXT("HPCount :; %f"), HealthCount);
	UE_LOG(LogTemp, Warning, TEXT("Status Count :; %d"), player->status.StatusCount);*/
}

void UStatusUI::Bullet_IncreaseValue()
{
	/*if (BulletCount < 0.99f && player->status.StatusCount != 0)
	{
		BulletCount += 0.05f;
		BulletScroll->SetPercent(BulletCount);

		player->status.StatusCount--;
		SetStatusCount(player->status.StatusCount);
	}
	UE_LOG(LogTemp, Warning, TEXT("HPCount :; %f"), BulletCount);
	UE_LOG(LogTemp, Warning, TEXT("Status Count :; %d"), player->status.StatusCount);*/
}

void UStatusUI::Bullet_DecreaseValue()
{
	/*if (BulletCount > 0.01f)
	{
		BulletCount -= 0.05f;
		BulletScroll->SetPercent(BulletCount);

		player->status.StatusCount++;
		SetStatusCount(player->status.StatusCount);
	}
	UE_LOG(LogTemp, Warning, TEXT("HPCount :; %f"), BulletCount);
	UE_LOG(LogTemp, Warning, TEXT("Status Count :; %d"), player->status.StatusCount);*/
}

void UStatusUI::Stamina_IncreaseValue()
{
	/*if (StaminaCount < 0.99f && player->status.StatusCount != 0)
	{
		StaminaCount += 0.05f;
		StaminaScroll->SetPercent(StaminaCount);

		player->status.StatusCount--;
		SetStatusCount(player->status.StatusCount);
	}
	UE_LOG(LogTemp, Warning, TEXT("HPCount :; %f"), StaminaCount);
	UE_LOG(LogTemp, Warning, TEXT("Status Count :; %d"), player->status.StatusCount);*/
}

void UStatusUI::Stamina_DecreaseValue()
{
	/*if (StaminaCount > 0.01f)
	{
		StaminaCount -= 0.05f;
		StaminaScroll->SetPercent(StaminaCount);

		player->status.StatusCount++;
		SetStatusCount(player->status.StatusCount);
	}
	UE_LOG(LogTemp, Warning, TEXT("HPCount :; %f"), StaminaCount);
	UE_LOG(LogTemp, Warning, TEXT("Status Count :; %d"), player->status.StatusCount);*/
}

void UStatusUI::SetStatusCount(int32 status)
{
	StatusCount->SetText(FText::AsNumber(status));
}
