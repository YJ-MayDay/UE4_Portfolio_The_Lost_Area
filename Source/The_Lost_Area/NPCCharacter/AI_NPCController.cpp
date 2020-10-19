// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_NPCController.h"
#include "NPCCharacter/NPCCharacter.h"

void AAI_NPCController::BeginPlay()
{
	Super::BeginPlay();
	OwnerChar = Cast<ANPCCharacter>(AController::K2_GetPawn());
	
	if(OwnerChar != nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Name Is :: %s"), *OwnerChar->GetName());


	switch (OwnerChar->GetKinds())
	{
	case ENPCKinds::none:
		break;

	case ENPCKinds::weapon_merchant:
		UE_LOG(LogTemp, Warning, TEXT("Test_Test_Test"));
		break;

	case ENPCKinds::item_merchant:
		break;

	case ENPCKinds::status:
		UE_LOG(LogTemp, Warning, TEXT("Check_Check_Check"));
		break;
	}

}


void AAI_NPCController::Tick(float DeltaSecends)
{
	Super::Tick(DeltaSecends);
	
}
