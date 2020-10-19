// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemMarketUI.generated.h"

/**
 * 
 */
UCLASS()
class THE_LOST_AREA_API UItemMarketUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItemList(TArray<struct FTB_ItemInfo*>& ItemDataList);
	//void SetInventoryList(TArray<struct FTB_ItemInfo*>& ItemDataList);
	
protected:

	UPROPERTY(EditDefaultsOnly) TSubclassOf<class UItemSlot> ItemSlotClass;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<class UInventorySlot> InventorySlotClass;
	
	class UInventorySlot* InventorySlot;

	UPROPERTY() class UScrollBox* ItemScroll;
	UPROPERTY() class UScrollBox* Inventory;
};
