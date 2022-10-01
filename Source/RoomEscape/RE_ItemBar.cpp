#include "RE_ItemBar.h"
#include "Components\ScrollBox.h"
#include "Components\ScrollBoxSlot.h"
#include "Components\VerticalBox.h"
#include "Components\VerticalBoxSlot.h"
#include "ItemSlot.h"
#include "AddCombine.h"
#include "Animation\WidgetAnimation.h"
#include "RE_GameInstance.h"


bool URE_ItemBar::Initialize()
{
	if (!Super::Initialize())
		return false;

	return true;
}


void URE_ItemBar::CreateItemSlot(UTexture2D* SetTexture, int32 SetItemNum)
{
	UItemSlot* ItemSlot = CreateWidget<UItemSlot>(this, ItemSlotClass);
	ItemSlot->SetItemSlotProperties(SetTexture, TenLimitItemSlotArray.Num(), SetItemNum);
	TenLimitItemSlotArray.Add(ItemSlot);


	UPanelSlot* ItemPanelSlot = ItemSlot_VerticalBox->AddChild(ItemSlot);
	UVerticalBoxSlot* ItemVerticalBoxSlot = Cast<UVerticalBoxSlot>(ItemPanelSlot);
	ItemVerticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	ItemVerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Top);
	FMargin mar;
	mar.Top = 30;
	ItemVerticalBoxSlot->SetPadding(mar);
	
}



void URE_ItemBar::DebugItemSlotArray()
{
	int32 i = 0;
	for (const auto& Element : TenLimitItemSlotArray)
	{
		UItemSlot* ItemSlot = Cast<UItemSlot>(Element);
		UE_LOG(LogTemp, Warning, TEXT("ItemNum : %d"), ItemSlot->GetItemNum());
		i++;
	}

}


int32 URE_ItemBar::GetItemSlotIndex(UItemSlot* FindItemSlot)
{
	int32 Index;
	if (TenLimitItemSlotArray.Find(FindItemSlot, Index))
	{
		UE_LOG(LogTemp, Warning, TEXT("URE_ItemBar::GetItemSlotIndex : %d"), Index);
	}
	return Index;
}


void URE_ItemBar::ShowWidget()
{
	if (MoveWidget)
	{
		PlayAnimation(MoveWidget,0,1,EUMGSequencePlayMode::Reverse);
	}
}

void URE_ItemBar::HiddenWidget()
{
	if (MoveWidget)
	{
		PlayAnimation(MoveWidget);
	}
}


