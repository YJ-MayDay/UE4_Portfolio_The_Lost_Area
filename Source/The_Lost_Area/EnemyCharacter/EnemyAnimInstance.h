// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"


UCLASS()
class THE_LOST_AREA_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	bool SetActivate(bool value);
	bool GetActivate() { return isActivate; }

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class AEnemyCharacter* OwnerChar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool isMove = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool isAttack = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool isActivate;
};
