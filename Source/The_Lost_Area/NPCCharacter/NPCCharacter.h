// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCCharacter.generated.h"

UENUM()
enum class ENPCKinds : uint8
{
	none,
	weapon_merchant,
	item_merchant,
	status,
	story
};

UCLASS()
class THE_LOST_AREA_API ANPCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANPCCharacter();

	virtual void Tick(float DeltaTime) override;

	void SetAmmoBuyWidget();
	void SetMarketWidget();

	ENPCKinds GetKinds() { return kinds; }

	bool GetIsPopup() { return ispopup; }

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		class AThe_Lost_AreaCharacter* Player;

	class APlayerController* PC;

	UPROPERTY(EditDefaultsOnly)
	ENPCKinds kinds;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	bool ispopup = true;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> WidgetClass;

	UPROPERTY()
		class UItemMarketUI* Market;
	UPROPERTY()
		class UAmmoBuyUI* AmmoBuy;

	UPROPERTY(EditDefaultsOnly)
		class UDataTable* ItemTable;
	UPROPERTY(EditDefaultsOnly)
		FName RowName;
	TArray<struct FTB_ItemInfo*> ItemList;
};
