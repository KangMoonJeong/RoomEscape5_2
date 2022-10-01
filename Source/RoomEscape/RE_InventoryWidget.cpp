#include "RE_InventoryWidget.h"
#include "Components\GridPanel.h"
#include "Components\GridSlot.h"
#include "Components\Border.h"
#include "RE_GameInstance.h"
#include "ItemSlot.h"
#include "RE_ItemSlotBarWidget.h"


bool URE_InventoryWidget::Initialize()
{
	bool Success = UUserWidget::Initialize();
	if (!Success)
		return false;

	UE_LOG(LogTemp, Warning, TEXT("URE_InventoryWidget::Initialize()  "))

	return true;
}






/* When Load Game, Open InventoryWidget from WholeWidget*/
void URE_InventoryWidget::InitializeData()
{
	InitializeItemSlotBarWidget();
	InitializeItemSlot_GridPanel();
}

void URE_InventoryWidget::InitializeItemSlot_GridPanel()
{
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (RE_GameInstance->GetTenLimitItemSlotArrayNum() == 0)
		return;


	TArray<class UItemSlot*> OtherLimitItemSlotArray;
	OtherLimitItemSlotArray = RE_GameInstance->GetOtherLimitItemSlotArray();

	int32 Row = 0;
	int32 Column = 0;

	for (int32 i = 0; i < OtherLimitItemSlotArray.Num(); i++)
	{
		if (!OtherLimitItemSlotArray.IsValidIndex(i))
			return;

		UGridSlot* GridSlot = ItemSlot_GridPanel->AddChildToGrid(OtherLimitItemSlotArray[i], Row, Column++);
		if (!GridSlot->IsValidLowLevel())
			return;
		GridSlot->SetPadding(FMargin(20.f));
		if (Column == 8)
		{
			Row++;
			Column = 0;
		}

	}
}

void URE_InventoryWidget::InitializeItemSlotBarWidget()
{
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (RE_GameInstance->GetTenLimitItemSlotArrayNum() == 0)
		return;

	ItemSlotBarWidget4->InitializeSlot();
}


