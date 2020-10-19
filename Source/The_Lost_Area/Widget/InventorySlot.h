// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "The_Lost_Area/The_Lost_AreaCharacter.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class THE_LOST_AREA_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetInventory(struct FInventoryList ItemInfo);
	void UpdateInventoryCount(int32 Value);

	struct FTB_ItemInfo* ItemData;
	struct FInventoryList InventoryData;

protected:
	
	UPROPERTY()
		class UImage* ItemIcon;

	UPROPERTY()
		class UTextBlock* ItemCount;

	UPROPERTY()
		int32 ItemNum = 0;
};
