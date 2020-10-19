// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "The_Lost_Area/The_Lost_AreaCharacter.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "The_Lost_Area/Widget/ItemMarketUI.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "The_Lost_Area/Widget/TB_ItemInfo.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "The_Lost_Area/Widget/AmmoBuyUI.h"

ANPCCharacter::ANPCCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<AThe_Lost_AreaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if (Player == nullptr)	return;

	PC = Cast<APlayerController>(Player->GetController());
	
	//UENUM 으로 설정한 NPC별 위젯을 플러이어가 접근했을 때 사용할수 있도록 세팅만 해주고 가려줍니다.
	switch (kinds)
	{
	case ENPCKinds::weapon_merchant:
		if (WidgetClass != nullptr)
		{
			AmmoBuy = CreateWidget<UAmmoBuyUI>(GetWorld(), WidgetClass);
			AmmoBuy->AddToViewport();
			AmmoBuy->SetVisibility(ESlateVisibility::Collapsed);
		}
		break;
	case ENPCKinds::item_merchant:
		if (WidgetClass != nullptr)
		{
			FString Context;
			ItemTable->GetAllRows<FTB_ItemInfo>(Context, ItemList);

			Market = CreateWidget<UItemMarketUI>(GetWorld(), WidgetClass);
			Market->AddToViewport();
			Market->SetItemList(ItemList);

			Market->SetVisibility(ESlateVisibility::Collapsed);
		}
		break;
	}
}

void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//플레이어가 일정 거리 안에서 E키 입력시 해당 위젯을 띄우며,
//SetInputMode 를 사용하여 위젯이 Visible 일 때, 마우스를 보이거나 보이지 않게 해주었습니다.
void ANPCCharacter::SetAmmoBuyWidget()
{
	if (ispopup)
	{
		AmmoBuy->SetVisibility(ESlateVisibility::Visible);
		AmmoBuy->SetScore(Player->status.Score);
		ispopup = false;

		PC->bShowMouseCursor = true;
		UWidgetBlueprintLibrary::SetInputMode_GameAndUI(PC, nullptr, false, false);
	}
	else
	{
		AmmoBuy->SetVisibility(ESlateVisibility::Collapsed);
		ispopup = true;

		PC->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);;
	}
}

void ANPCCharacter::SetMarketWidget()
{
	if (ispopup)
	{
		Market->SetVisibility(ESlateVisibility::Visible);
		ispopup = false;

		PC->bShowMouseCursor = true;
		UWidgetBlueprintLibrary::SetInputMode_GameAndUI(PC, nullptr, false,false);
	}
	else
	{
		Market->SetVisibility(ESlateVisibility::Collapsed);
		ispopup = true;

		PC->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);;
	}
}


