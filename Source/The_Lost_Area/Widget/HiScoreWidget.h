// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HiScoreWidget.generated.h"

UCLASS()
class THE_LOST_AREA_API UHiScoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//void OnclickedCheck();
	void SetData();

	float Opacity = 1.0f;
	float DeltaValue = 0.025f;

	UPROPERTY() class UTextBlock* Press;

	UPROPERTY() class UTextBlock* ViewKills_0;
	UPROPERTY() class UTextBlock* ViewUsedBullet_0;
	UPROPERTY() class UTextBlock* ViewGameScore_0;
	UPROPERTY() class UTextBlock* ViewTotalScore_0;
	UPROPERTY() class UTextBlock* ViewPlayerName_0;

	UPROPERTY() class UTextBlock* ViewKills_1;
	UPROPERTY() class UTextBlock* ViewUsedBullet_1;
	UPROPERTY() class UTextBlock* ViewGameScore_1;
	UPROPERTY() class UTextBlock* ViewTotalScore_1;
	UPROPERTY() class UTextBlock* ViewPlayerName_1;

	UPROPERTY() class UTextBlock* ViewKills_2;
	UPROPERTY() class UTextBlock* ViewUsedBullet_2;
	UPROPERTY() class UTextBlock* ViewGameScore_2;
	UPROPERTY() class UTextBlock* ViewTotalScore_2;
	UPROPERTY() class UTextBlock* ViewPlayerName_2;

	UPROPERTY() class UTextBlock* ViewKills_3;
	UPROPERTY() class UTextBlock* ViewUsedBullet_3;
	UPROPERTY() class UTextBlock* ViewGameScore_3;
	UPROPERTY() class UTextBlock* ViewTotalScore_3;
	UPROPERTY() class UTextBlock* ViewPlayerName_3;

	UPROPERTY() class UTextBlock* ViewKills_4;
	UPROPERTY() class UTextBlock* ViewUsedBullet_4;
	UPROPERTY() class UTextBlock* ViewGameScore_4;
	UPROPERTY() class UTextBlock* ViewTotalScore_4;
	UPROPERTY() class UTextBlock* ViewPlayerName_4;

	UPROPERTY() class UTextBlock* NowKills;
	UPROPERTY() class UTextBlock* NowUsedBullet;
	UPROPERTY() class UTextBlock* NowGameScore;
	UPROPERTY() class UTextBlock* NowTotalScore;
	UPROPERTY() class UTextBlock* NowPlayerName;

	UPROPERTY() class UButton* MainTitle;

};
