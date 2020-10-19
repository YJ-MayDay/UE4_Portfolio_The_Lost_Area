// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDataInstance.h"

FText UGameDataInstance::SetPlayerName(FText Name)
{
	return PlayerName = Name;
}

int32 UGameDataInstance::SetGameScore(int32 Value)
{
	return NowScore = Value;
}

int32 UGameDataInstance::SetKills()
{
	return NowKills++;
}

int32 UGameDataInstance::SetUsedBullet(int32 Value)
{
	return NowUsedBullet = Value;
}

