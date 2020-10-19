// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StatusStruct.generated.h"

USTRUCT(Atomic, BlueprintType)
struct THE_LOST_AREA_API FStatusStruct
{
	GENERATED_USTRUCT_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 HealthPoint = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 AttackDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 DefensePoint = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RunSpeed = 0;
};

USTRUCT(Atomic, BlueprintType)
struct THE_LOST_AREA_API FCharacterStatusStruct : public FStatusStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxHealthPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Score = 0;

};

USTRUCT(Atomic, BlueprintType)
struct THE_LOST_AREA_API FEnemyStatusStruct : public FStatusStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxHealthPoint;

};
