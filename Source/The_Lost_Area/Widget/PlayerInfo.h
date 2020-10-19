// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "The_Lost_Area/The_Lost_AreaCharacter.h"
#include "PlayerInfo.generated.h"

/**
 * 
 */
UCLASS()
class THE_LOST_AREA_API UPlayerInfo : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;

	class AThe_Lost_AreaCharacter* Player;

	UPROPERTY()
	class UTextBlock* CurrentAmmoCount;

	UPROPERTY()
	class UTextBlock* TotalAmmoCount;

	UPROPERTY()
		class UImage* BloodImage;

	UPROPERTY()
		class UScrollBox* ShowItemIcon;
	
	UPROPERTY()
	class UImage* ShowIcon;

	UPROPERTY()
		class UTextBlock* ShowCount;

	UPROPERTY()
		class UTextBlock* Score;
	
	UPROPERTY()
		class UTextBlock* DefenseCount;

	UPROPERTY()
		class UTextBlock* RoundCount;

	UPROPERTY()
		class UTextBlock* EnemyCount;

	UPROPERTY()
		class UTextBlock* PlayerHP;

	UPROPERTY()
		class UTextBlock* Damage;

	UPROPERTY()
		class UTextBlock* Press;

	float opacity = 1.0f;
	float DeltaValue = 0.025f;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	
	UPROPERTY()
		TArray<FInventoryList> ShowItem;

	UFUNCTION()
		void SetShowItemCount(struct FInventoryList Inven);

	UFUNCTION()
		void SetAmmoCount(int32 AmmoCount);

	UFUNCTION()
		void SetTotalAmmoCount(int32 totalCount);

	UFUNCTION()
		void SetOpacity(int32 FadeValue);

	UFUNCTION()
		void SetScore(int32 ScoreValue);

	UFUNCTION()
		void SetDefenseCount(int32 DefenseValue);
};
