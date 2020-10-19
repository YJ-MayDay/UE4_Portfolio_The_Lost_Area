// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainTitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class THE_LOST_AREA_API UMainTitleWidget : public UUserWidget
{
	GENERATED_BODY()

		virtual void NativeOnInitialized() override;

public:

	UFUNCTION()
	void OnStartClick();

protected:

	UFUNCTION()
	void OnCheckButton();

	UPROPERTY()
	class UButton* Start;

	UPROPERTY()
	class UButton* Exit;

	UPROPERTY()
	class UTextBlock* TItleText;

	UPROPERTY(BlueprintReadWrite)
		class UImage* Image;

	UPROPERTY(BlueprintReadOnly)
		bool IsFade = false;

	UPROPERTY()
		class UCanvasPanel* InputName;

	UPROPERTY()
		class UEditableTextBox* PlayerName;

	UPROPERTY()
		class UButton* CheckButton;

	bool isPlayerNameInput = false;

};
