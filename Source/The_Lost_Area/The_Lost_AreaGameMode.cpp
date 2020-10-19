// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "The_Lost_AreaGameMode.h"
#include "The_Lost_AreaCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "The_Lost_Area/GM_RespawnSpot.h"

AThe_Lost_AreaGameMode::AThe_Lost_AreaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AThe_Lost_AreaGameMode::SetRespawnSpot()
{
	TArray<AActor*> RespawnSpots2;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGM_RespawnSpot::StaticClass(), RespawnSpots);

	UE_LOG(LogTemp, Warning, TEXT("RespawnSpots Num :: %d"), RespawnSpots.Num());
}
