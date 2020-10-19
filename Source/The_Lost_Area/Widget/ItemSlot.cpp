// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlot.h"
#include "The_Lost_Area/Widget/TB_ItemInfo.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "The_Lost_Area/The_Lost_AreaCharacter.h"
#include "The_Lost_Area/Widget/Inventory.h"
#include "The_Lost_Area/Widget/PlayerInfo.h"

//불러온 CSV 데이터을 각각의 슬롯으로 만듭니다.
void UItemSlot::SetItemInfo(struct FTB_ItemInfo* itemInfo)
{
	ItemData = itemInfo;

	ItemImage->SetBrushFromSoftTexture(itemInfo->TextureIcon);
	Price->SetText(FText::AsNumber(itemInfo->BuyPrice));
	Name->SetText(itemInfo->Name);
}

//마우스 왼쪽 버튼을 클릭하는 것으로 아이템을 구입하는 함수입니다.
//클릭한 아이템이 장비용 아이템이면 표시된 방어력을 늘려주고
//일반 사용 아이템이면 인벤토리 아이템 카운터를 올려줍니다.
FReply UItemSlot::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	FKey key = FKey(EKeys::LeftMouseButton);
	FEventReply eventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, key);
	
	AThe_Lost_AreaCharacter* Player = Cast<AThe_Lost_AreaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FString TestName = this->Name->Text.ToString();

	if (ItemData->Kinds != EItemKinds::Equipment)
	{
		for (int32 i = 0; i < Player->Inventory.Num(); i++)
		{
			FString ItemName = Player->Inventory[i].Name.ToString();
			if (TestName.Equals(ItemName) && Player->status.Score - ItemData->BuyPrice >= 0)
			{
				Player->Inventory[i].ItemCount++;

				Player->status.Score -= ItemData->BuyPrice;
				Player->Inventory2->SetInventoryList();

				Player->Info->ShowItem[0].ItemCount = Player->Inventory[i].ItemCount;
			}
		}
	}
	else
	{
		if (Player->status.Score - ItemData->BuyPrice >= 0)
		{
			Player->status.Score -= ItemData->BuyPrice;
			Player->status.DefensePoint += ItemData->StatusValue;
			Player->Inventory2->SetInventoryList();
		}
	}
	
	return eventReply.NativeReply;
}
