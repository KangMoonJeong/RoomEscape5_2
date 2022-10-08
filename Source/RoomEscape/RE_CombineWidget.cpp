#include "RE_CombineWidget.h"
#include "RE_GameInstance.h"
#include "RE_CombineItemSlot.h"
#include "ItemSlot.h"
#include "FP_FirstPerson\FP_FirstPersonCharacter.h"
#include "RE_PlayerController.h"
#include "Components\UniformGridPanel.h"


bool URE_CombineWidget::Initialize()
{
	if (!Super::Initialize())
		return false;

	FirstCombineItemSlot->SetParentWidget(this);
	SecondCombineItemSlot->SetParentWidget(this);

	return true;
}





/* Initial Settings */
void URE_CombineWidget::InitialSetting()
{
	InitializeItemSlot_GridPanel();
}

void URE_CombineWidget::InitializeItemSlot_GridPanel()
{
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (RE_GameInstance->GetTenLimitItemSlotArrayNum() == 0)
		return;


	TArray<class UItemSlot*> NoLimitItemSlotArray;
	NoLimitItemSlotArray = RE_GameInstance->GetNoLimitItemSlotArray();

	Row = 0;
	Column = 0;

	for (int32 i = 0; i < NoLimitItemSlotArray.Num(); i++)
	{
		if (!NoLimitItemSlotArray[i]->IsValidLowLevel())
			continue;

		UWidget* ItemSlot = NoLimitItemSlotArray[i];
		ItemSlot_UniformGridPanel->AddChildToUniformGrid(ItemSlot, Row, Column);

		Column++;
		if (Column == 8)
		{
			Row++;
			Column = 0;
		}
	}
}

void URE_CombineWidget::InitializeCombineItemSlot()
{
	FirstCombineItemSlot->SetParentWidget(this);
	SecondCombineItemSlot->SetParentWidget(this);

}





/* Combine and Add Item Slot */
void URE_CombineWidget::AddItemSlot_GridPanel()
{
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (RE_GameInstance->GetTenLimitItemSlotArrayNum() == 0)
		return;


	TArray<class UItemSlot*> NoLimitItemSlotArray;
	NoLimitItemSlotArray = RE_GameInstance->GetNoLimitItemSlotArray();


	ItemSlot_UniformGridPanel->AddChildToUniformGrid(NoLimitItemSlotArray[NoLimitItemSlotArray.Num() - 1], Row, Column++);
	//GridSlot->SetPadding(FMargin(20.f));
	if (Column == 8)
	{
		Row++;
		Column = 0;
	}
}

void URE_CombineWidget::CreateItemSlot(int32 ItemNum)
{
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (!RE_GameInstance)
		return;

	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;


	if (RE_GameInstance->SetTenLimitItemSlotArrayElement(ItemNum))
	{
		RE_GameInstance->SetTenLimitItemSlotDataMap(ItemNum, true);
	}
	else
	{
		RE_GameInstance->SetOtherLimitItemSlotArrayElement(ItemNum);
		RE_GameInstance->SetOtherLimitItemSlotDataMap(ItemNum, true);
	}

	RE_GameInstance->SetNoLimitItemSlotArrayElement(ItemNum);
	RE_GameInstance->SetNoLimitItemSlotDataMap(ItemNum, true);


	// AddItemSlot_GridPanel();
	RE_GameInstance->GetItem(ItemNum);
}

void URE_CombineWidget::InspectionAddStatus()
{
	int32 FirstItemNum = FirstCombineItemSlot->GetItemNum();
	int32 SecondItemNum = SecondCombineItemSlot->GetItemNum();


	for (auto& Elem : CombineListArray)
	{
		if (Elem.FirstItemNum == FirstItemNum && Elem.SecondItemNum == SecondItemNum)
		{
			DeleteItemSlot(FirstItemNum, SecondItemNum);
			CreateItemSlot(Elem.ResultItemNum);
			ReLocationItemSlot_GridPanel();
			ClearCombineItemSlot();
		}
		else if (Elem.SecondItemNum == FirstItemNum && Elem.FirstItemNum == SecondItemNum)
		{
			DeleteItemSlot(FirstItemNum, SecondItemNum);
			CreateItemSlot(Elem.ResultItemNum);
			ReLocationItemSlot_GridPanel();
			ClearCombineItemSlot();
		}
	}
}

void URE_CombineWidget::ReLocationItemSlot_GridPanel()
{
	ItemSlot_UniformGridPanel->ClearChildren();
	InitializeItemSlot_GridPanel();
}



void URE_CombineWidget::DeleteItemSlot(int32 FirstItemNum, int32 SecondItemNum)
{
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (!RE_GameInstance)
		return;

	RE_GameInstance->DeleteTenLimitArrayElementByItemNum(FirstItemNum);
	RE_GameInstance->DeleteTenLimitArrayElementByItemNum(SecondItemNum);

	RE_GameInstance->DeleteOtherLimitArrayElementByItemNum(FirstItemNum);
	RE_GameInstance->DeleteOtherLimitArrayElementByItemNum(SecondItemNum);

	RE_GameInstance->DeleteNoLimitArrayElementByItemNum(FirstItemNum);
	RE_GameInstance->DeleteNoLimitArrayElementByItemNum(SecondItemNum);
}


void URE_CombineWidget::ClearCombineItemSlot()
{
	FirstCombineItemSlot->CleanItemSlot();
	SecondCombineItemSlot->CleanItemSlot();
}