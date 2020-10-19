// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameMode.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "The_Lost_Area/Widget/HiScoreWidget.h"
#include "The_Lost_Area/EndGameMode/TB_HiScore.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerInput.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AEndGameMode::AEndGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

}

void AEndGameMode::Tick(float DeltaSecends)
{
	Super::Tick(DeltaSecends);
}

void AEndGameMode::BeginPlay()
{
	FString Context;
	HiScoreTable->GetAllRows<FTB_HiScore>(Context, ScoreList);

	if (HiScoreClass == nullptr) return;
		
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), HiScoreClass);
	Widget->AddToViewport();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	PC->bShowMouseCursor = true;

}
