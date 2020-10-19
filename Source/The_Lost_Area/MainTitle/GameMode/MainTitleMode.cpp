// Fill out your copyright notice in the Description page of Project Settings.


#include "MainTitleMode.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MainTitle/UserWidget/MainTitleWidget.h"

AMainTitleMode::AMainTitleMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainTitleMode::BeginPlay()
{
	Super::BeginPlay();

	if (MainTitleClass != nullptr)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainTitleClass);
		TitleWidget = Cast<UMainTitleWidget>(Widget);
	}
}

void AMainTitleMode::Tick(float DeltaSecends)
{
	Super::Tick(DeltaSecends);
}

void AMainTitleMode::StartGame(float FadeDuration)
{
	FTimerHandle TimerHandler;
	GetWorldTimerManager().SetTimer(TimerHandler, this, &AMainTitleMode::ChangeLevel, FadeDuration, false);
}

void AMainTitleMode::ChangeLevel()
{
	if (LevelName.IsValid())
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	else
		return;

}

