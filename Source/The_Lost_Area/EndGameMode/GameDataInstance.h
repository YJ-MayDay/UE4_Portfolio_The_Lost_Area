// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameDataInstance.generated.h"

UCLASS()
class THE_LOST_AREA_API UGameDataInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	FText GetPlayerName() { return PlayerName; }
	FText SetPlayerName(FText Name);

	int32 GetGameScore() { return NowScore; }
	int32 SetGameScore(int32 Value);

	int32 GetKills() { return NowKills; }
	int32 SetKills();

	int32 GetUsedBullet() { return NowUsedBullet; }
	int32 SetUsedBullet(int32 Value);
protected:

	int32 NowScore;
	int32 NowKills;
	int32 NowUsedBullet;
	FText PlayerName;
};
