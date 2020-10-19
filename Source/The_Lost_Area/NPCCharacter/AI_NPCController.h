// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_NPCController.generated.h"

/**
 * 
 */
UCLASS()
class THE_LOST_AREA_API AAI_NPCController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSecends) override;

	class ANPCCharacter* OwnerChar;
};
