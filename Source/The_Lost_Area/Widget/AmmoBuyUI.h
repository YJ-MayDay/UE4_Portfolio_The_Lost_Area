// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmmoBuyUI.generated.h"

/**
 * 
 */
UCLASS()
class THE_LOST_AREA_API UAmmoBuyUI : public UUserWidget
{
	GENERATED_BODY()


	virtual void NativeOnInitialized() override;

	class AThe_Lost_AreaCharacter* Player;

	UPROPERTY()
		int32 money;

	UPROPERTY()
		class UTextBlock* Cash;

	UPROPERTY()
		class UButton* Bullet556;

	UPROPERTY()
		class UButton* Bullet762;

	UPROPERTY()
		class UButton* HPup;

	UPROPERTY()
		class UButton* DamageUP;

	UPROPERTY()
		class UButton* BulletUP;

	UFUNCTION()
		void BuyBullet556();

	UFUNCTION()
		void BuyBullet762();

	UFUNCTION()
		void BuyHPup();

	UFUNCTION()
		void BuyDamageUP();

		UFUNCTION()
		void BuyMaxBulletUP();

public:
	UFUNCTION()
		void SetScore(int32 ScoreValue);

protected:

	int32 Bullet556_Price;
	int32 Bullet762_Price;
	int32 HPup_Price;
	int32 Damage_Price;
	int32 Bullet_Price;
};
