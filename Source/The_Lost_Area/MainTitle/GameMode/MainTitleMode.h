// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainTitleMode.generated.h"

UCLASS()
class THE_LOST_AREA_API AMainTitleMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AMainTitleMode();

	virtual void Tick(float DeltaSecends) override;

	UFUNCTION(BlueprintCallable)
		void ChangeLevel();

	UFUNCTION()
		void StartGame(float FadeDuration);

protected:
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere)
		float DelayTime = 2.f;

	UPROPERTY(EditDefaultsOnly)
		FName LevelName;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> MainTitleClass;

	UPROPERTY(BlueprintReadWrite)
	class UMainTitleWidget* TitleWidget;

};
