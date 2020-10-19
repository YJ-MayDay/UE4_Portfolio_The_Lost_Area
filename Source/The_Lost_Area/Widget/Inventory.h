// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class THE_LOST_AREA_API UInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetInventoryList();

protected:
	UPROPERTY(EditDefaultsOnly) TSubclassOf<class UInventorySlot> InventorySlotClass;

	UPROPERTY()
		class UWrapBox* InvnetoryBox;

	UPROPERTY()
		class UInventorySlot* InventorySlot;
};
