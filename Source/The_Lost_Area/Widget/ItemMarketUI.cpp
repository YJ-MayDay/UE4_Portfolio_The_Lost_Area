// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMarketUI.h"
#include "The_Lost_Area/Widget/ItemSlot.h"
#include "The_Lost_Area/Widget/InventorySlot.h"
#include "Runtime/UMG/Public/Components/ScrollBox.h"
#include "The_Lost_Area/Widget/TB_ItemInfo.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "The_Lost_Area/The_Lost_AreaCharacter.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"

void UItemMarketUI::SetItemList(TArray<struct FTB_ItemInfo*>& ItemDataList)
{
	if (ItemSlotClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Exist Item Slot Class"));
		return;
	}

	for (FTB_ItemInfo* itemData : ItemDataList)
	{
		if (itemData->Kinds != EItemKinds::None)
		{
			UItemSlot* ItemSlot = CreateWidget<UItemSlot>(GetWorld(), ItemSlotClass);
			ItemSlot->AddToViewport();
			ItemSlot->SetItemInfo(itemData);
			ItemScroll->AddChild(ItemSlot);
		}
	}
}
