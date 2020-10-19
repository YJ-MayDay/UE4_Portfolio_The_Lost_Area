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
	
	//UENUM ���� ������ NPC�� ������ �÷��̾ �������� �� ����Ҽ� �ֵ��� ���ø� ���ְ� �����ݴϴ�.
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

//�÷��̾ ���� �Ÿ� �ȿ��� EŰ �Է½� �ش� ������ ����,
//SetInputMode �� ����Ͽ� ������ Visible �� ��, ���콺�� ���̰ų� ������ �ʰ� ���־����ϴ�.
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


