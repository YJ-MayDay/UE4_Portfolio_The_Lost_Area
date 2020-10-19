// Fill out your copyright notice in the Description page of Project Settings.


#include "HiScoreWidget.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/Core/Public/Internationalization/Text.h"
#include "The_Lost_Area/EndGameMode/GameDataInstance.h"
#include "The_Lost_Area/EndGameMode/TB_HiScore.h"
#include "The_Lost_Area/EndGameMode/EndGameMode.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Components/Button.h"

void UHiScoreWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetData();
}

void UHiScoreWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	AEndGameMode* GameMode = Cast<AEndGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UHiScoreWidget::SetData()
{
	AEndGameMode* GameMode = Cast<AEndGameMode>(GetWorld()->GetAuthGameMode());

	//임시로 만들어 놓은 HiScore CSV를 로드하고
	TArray<FTB_HiScore*> Score = GameMode->GetScoreList();

	UGameDataInstance* Instance = Cast<UGameDataInstance>(GetWorld()->GetGameInstance());

	//임시 스코어변수 선언 후, GameInstance의 스코어 데이터와 PlayerName을 넣어주고
	FTB_HiScore* InputScore = new FTB_HiScore;
	InputScore->Kills = Instance->GetKills();
	InputScore->UsedBullet = Instance->GetUsedBullet();
	InputScore->GameScore = Instance->GetGameScore();

	FString str = Instance->GetPlayerName().ToString();
	InputScore->PlayerName = FName(*str);
	InputScore->TotalScore = ((InputScore->Kills * 10) + (InputScore->UsedBullet * 10) + InputScore->GameScore);

	//로드한 스코어에 넣은 후 Sort를 사용해 값을 비교해 순차적으로 세팅해 주는 코드입니다.
	Score.Add(InputScore);

	Score.Sort([](FTB_HiScore& A, FTB_HiScore& B)
	{
		return A.TotalScore > B.TotalScore;
	});

	ViewKills_0->SetText(FText::AsNumber(Score[0]->Kills));
	ViewUsedBullet_0->SetText(FText::AsNumber(Score[0]->UsedBullet));
	ViewGameScore_0->SetText(FText::AsNumber(Score[0]->GameScore));
	ViewTotalScore_0->SetText(FText::AsNumber(Score[0]->TotalScore));
	ViewPlayerName_0->SetText(FText::FromName(Score[0]->PlayerName));

	ViewKills_1->SetText(FText::AsNumber(Score[1]->Kills));
	ViewUsedBullet_1->SetText(FText::AsNumber(Score[1]->UsedBullet));
	ViewGameScore_1->SetText(FText::AsNumber(Score[1]->GameScore));
	ViewTotalScore_1->SetText(FText::AsNumber(Score[1]->TotalScore));
	ViewPlayerName_1->SetText(FText::FromName(Score[1]->PlayerName));

	ViewKills_2->SetText(FText::AsNumber(Score[2]->Kills));
	ViewUsedBullet_2->SetText(FText::AsNumber(Score[2]->UsedBullet));
	ViewGameScore_2->SetText(FText::AsNumber(Score[2]->GameScore));
	ViewTotalScore_2->SetText(FText::AsNumber(Score[2]->TotalScore));
	ViewPlayerName_2->SetText(FText::FromName(Score[2]->PlayerName));

	ViewKills_3->SetText(FText::AsNumber(Score[3]->Kills));
	ViewUsedBullet_3->SetText(FText::AsNumber(Score[3]->UsedBullet));
	ViewGameScore_3->SetText(FText::AsNumber(Score[3]->GameScore));
	ViewTotalScore_3->SetText(FText::AsNumber(Score[3]->TotalScore));
	ViewPlayerName_3->SetText(FText::FromName(Score[3]->PlayerName));

	ViewKills_4->SetText(FText::AsNumber(Score[4]->Kills));
	ViewUsedBullet_4->SetText(FText::AsNumber(Score[4]->UsedBullet));
	ViewGameScore_4->SetText(FText::AsNumber(Score[4]->GameScore));
	ViewTotalScore_4->SetText(FText::AsNumber(Score[4]->TotalScore));
	ViewPlayerName_4->SetText(FText::FromName(Score[4]->PlayerName));

	NowKills->SetText(FText::AsNumber(InputScore->Kills));
	NowUsedBullet->SetText(FText::AsNumber(InputScore->UsedBullet));
	NowGameScore->SetText(FText::AsNumber(InputScore->GameScore));
	NowTotalScore->SetText(FText::AsNumber(InputScore->TotalScore));
	NowPlayerName->SetText(FText::FromName(InputScore->PlayerName));
}

