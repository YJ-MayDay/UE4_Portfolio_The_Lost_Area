// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CrossHairHUD.generated.h"

/**
 * 
 */
UCLASS()
class THE_LOST_AREA_API ACrossHairHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;


protected:
	UPROPERTY(EditDefaultsOnly)
		UTexture2D* CrossHairTexture;

};
