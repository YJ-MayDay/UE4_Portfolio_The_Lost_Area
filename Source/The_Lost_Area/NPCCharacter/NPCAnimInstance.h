// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NPCAnimInstance.generated.h"

UCLASS()
class THE_LOST_AREA_API UNPCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeBeginPlay() override;

protected:
	class ANPCCharacter* OwnerChar;
	class AThe_Lost_AreaCharacter* Player;
	class APlayerController* PC;

	UPROPERTY(BlueprintReadOnly)
		bool UIPopup = false;

	UPROPERTY(BlueprintReadOnly)
		float Distance;

	UPROPERTY(BlueprintReadOnly)
		float InterectionCheck;
};
