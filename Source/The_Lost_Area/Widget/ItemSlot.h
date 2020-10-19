// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class THE_LOST_AREA_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetItemInfo(struct FTB_ItemInfo* itemInfo);


protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	struct FTB_ItemInfo* ItemData;

	UPROPERTY()
		class UImage* ItemImage;
	UPROPERTY()
		class UTextBlock* Price;
	UPROPERTY()
		class UTextBlock* Name;
};
