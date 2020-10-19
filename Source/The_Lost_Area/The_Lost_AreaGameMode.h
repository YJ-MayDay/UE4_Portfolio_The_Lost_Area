// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "The_Lost_AreaGameMode.generated.h"

UCLASS(minimalapi)
class AThe_Lost_AreaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AThe_Lost_AreaGameMode();

protected:

	TArray<AActor*> RespawnSpots;

	void SetRespawnSpot();
};



