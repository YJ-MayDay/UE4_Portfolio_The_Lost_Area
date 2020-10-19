// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "The_Lost_Area/Widget/TB_ItemInfo.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "The_Lost_Area/The_Lost_AreaCharacter.h"

void UInventorySlot::SetInventory(struct FInventoryList ItemInfo)
{
	AThe_Lost_AreaCharacter* Player = Cast<AThe_Lost_AreaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	InventoryData = ItemInfo;

	ItemIcon->SetBrushFromSoftTexture(ItemInfo.Icon);

	ItemCount->SetText(FText::AsNumber(ItemInfo.ItemCount));

}

void UInventorySlot::UpdateInventoryCount(int32 Value)
{
	ItemCount->SetText(FText::AsNumber(Value));
}
