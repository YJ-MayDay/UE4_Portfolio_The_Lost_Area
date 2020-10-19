// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TB_ItemInfo.generated.h"

UENUM(BlueprintType)
enum class EStatusType : uint8
{
	None,
	AttackDamage,
	HP,
	Deffense,

};

UENUM(BlueprintType)
enum class EItemKinds : uint8
{
	None,
	Ammo,
	Equipment,
	Consumeable
};

USTRUCT(BlueprintType)
struct THE_LOST_AREA_API FTB_ItemInfo : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly) FText Name;
	UPROPERTY(EditDefaultsOnly) EItemKinds Kinds;
	UPROPERTY(EditDefaultsOnly) int32 BuyPrice;
	UPROPERTY(EditDefaultsOnly) int32 SellPrice;
	UPROPERTY(EditDefaultsOnly) EStatusType StatusType;
	UPROPERTY(EditDefaultsOnly) int32 StatusValue;
	UPROPERTY(EditDefaultsOnly) TSoftObjectPtr<class UTexture2D> TextureIcon;


};
