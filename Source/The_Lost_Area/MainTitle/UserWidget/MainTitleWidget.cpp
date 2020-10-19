// Fill out your copyright notice in the Description page of Project Settings.


#include "MainTitleWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "MainTitle/GameMode/MainTitleMode.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "The_Lost_Area/EndGameMode/GameDataInstance.h"

void UMainTitleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	// UMG 버튼 델리게이트 
	if (Start != nullptr)
		Start->OnClicked.AddDynamic(this, &UMainTitleWidget::OnStartClick);

	if (CheckButton != nullptr)
		CheckButton->OnClicked.AddDynamic(this, &UMainTitleWidget::OnCheckButton);

	InputName->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainTitleWidget::OnStartClick()
{
	InputName->SetVisibility(ESlateVisibility::Visible);
}

void UMainTitleWidget::OnCheckButton()
{
	//GetPlayerName & Instance PlayerName 세팅
	FText TempText = PlayerName->GetText();

	UGameDataInstance* Instance = Cast<UGameDataInstance>(GetWorld()->GetGameInstance());
	Instance->SetPlayerName(TempText);

	FString str = TempText.ToString();
	UE_LOG(LogTemp, Warning, TEXT("TempText Is %s"), *str);

	if (!TempText.IsEmpty())
		isPlayerNameInput = true;

	AMainTitleMode* GameMode = GetWorld()->GetAuthGameMode<AMainTitleMode>();
	if (GameMode != nullptr && isPlayerNameInput)
	{
		IsFade = true;
		Image->SetVisibility(ESlateVisibility::Visible);
		GameMode->StartGame(2.0f);
	}
}


