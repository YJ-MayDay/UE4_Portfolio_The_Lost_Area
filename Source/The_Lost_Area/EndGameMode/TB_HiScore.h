// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TB_HiScore.generated.h"

USTRUCT(BlueprintType)
struct THE_LOST_AREA_API FTB_HiScore : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly) int32 Kills;
	UPROPERTY(EditDefaultsOnly) int32 GameScore;
	UPROPERTY(EditDefaultsOnly) int32 UsedBullet;
	UPROPERTY(EditDefaultsOnly) int32 TotalScore;
	UPROPERTY(EditDefaultsOnly) FName PlayerName;

	FTB_HiScore()
	{
		Kills = 0;
		GameScore = 0;
		UsedBullet = 0;
		TotalScore = 0;
	}
};
