// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndGameMode.generated.h"

UCLASS()
class THE_LOST_AREA_API AEndGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AEndGameMode();

public:
	TArray<struct FTB_HiScore*> GetScoreList() { return ScoreList; }

	virtual void Tick(float DeltaSecends);
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHiScoreWidget> HiScoreClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDataTable* HiScoreTable;

	TArray<struct FTB_HiScore*> ScoreList;
};
