// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "The_Lost_Area/Widget/InventorySlot.h"
#include "Runtime/UMG/Public/Components/WrapBox.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UInventory::SetInventoryList()
{
	InvnetoryBox->ClearChildren();

	AThe_Lost_AreaCharacter* Player = Cast<AThe_Lost_AreaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	for (int32 i = 0; i < Player->Inventory.Num(); i++)
	{
		FInventoryList InventoryData = Player->Inventory[i];

		InventorySlot = CreateWidget<UInventorySlot>(GetWorld(), InventorySlotClass);
		InventorySlot->AddToViewport();
		InventorySlot->SetInventory(InventoryData);
		InvnetoryBox->AddChild(InventorySlot);

	}
}