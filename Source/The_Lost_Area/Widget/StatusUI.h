// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusUI.generated.h"

/**
 * 
 */
UCLASS()
class THE_LOST_AREA_API UStatusUI : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;

public:
	void SetStatusCount(int32 StatusCount);

	UPROPERTY(EditDefaultsOnly)
		float StaminaCount;

protected:

	UPROPERTY()
		class AThe_Lost_AreaCharacter* player;

	UPROPERTY(EditDefaultsOnly)
		int32 TotalStatusCount;

	UPROPERTY(EditDefaultsOnly)
		class UTextBlock* StatusCount;

	UFUNCTION()
		void SetChangeUpText(int TotalCount);

	//Health
	UPROPERTY(EditDefaultsOnly)
		float HealthCount;

	UPROPERTY(EditDefaultsOnly)
		class UButton* Health_L;

	UPROPERTY(EditDefaultsOnly)
		class UButton* Health_R;

	UPROPERTY(EditDefaultsOnly)
		class UProgressBar* HealthScroll;

	UFUNCTION()
		void Health_IncreaseValue();

	UFUNCTION()
		void Health_DecreaseValue();

	//

	//Bullet
	UPROPERTY(EditDefaultsOnly)
		float BulletCount;

	UPROPERTY(EditDefaultsOnly)
		class UButton* Bullet_L;

	UPROPERTY(EditDefaultsOnly)
		class UButton* Bullet_R;

	UPROPERTY(EditDefaultsOnly)
		class UProgressBar* BulletScroll;

	UFUNCTION()
		void Bullet_IncreaseValue();

	UFUNCTION()
		void Bullet_DecreaseValue();
	//

	//Stamina
	/*UPROPERTY(EditDefaultsOnly)
		float StaminaCount;*/

	UPROPERTY(EditDefaultsOnly)
	class UButton* Stamina_L;

	UPROPERTY(EditDefaultsOnly)
		class UButton* Stamina_R;

	UPROPERTY(EditDefaultsOnly)
		class UProgressBar* StaminaScroll;

	UFUNCTION()
		void Stamina_IncreaseValue();

	UFUNCTION()
		void Stamina_DecreaseValue();


};
