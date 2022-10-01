#include "RE_ItemInsepctionWidget.h"
#include "Components\GridPanel.h"
#include "Components\GridSlot.h"
#include "Components/Button.h"
#include "RE_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Inspection_Interface.h"
#include "ItemSlotInteraction_Interface.h"
#include "RE_GameInstance.h"
#include "ItemSlot.h"


bool URE_ItemInsepctionWidget::Initialize()
{
	bool Success = UUserWidget::Initialize();
	if (!Success)
		return false;

	Left_Button->OnClicked.AddDynamic(this, &URE_ItemInsepctionWidget::Left_ButtonOnClicked);
	Right_Button->OnClicked.AddDynamic(this, &URE_ItemInsepctionWidget::Right_ButtonOnClicked);

	return true;
}





/* Setting */
void URE_ItemInsepctionWidget::InitialInputSetting()
{
	TArray<AActor*> InterfaceActor;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInspection_Interface::StaticClass(), InterfaceActor);
	for (AActor* Actor : InterfaceActor)
	{
		IInspection_Interface* Inspection_Interface = Cast<IInspection_Interface>(Actor);
		Inspection_Interface->StartInteractionSetting();
	}

	ARE_PlayerController* PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	FInputModeGameAndUI InputMode;
	PlayerController->SetInputMode(InputMode);
}

void URE_ItemInsepctionWidget::InitializeItemSlot_GridPanel()
{
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (RE_GameInstance->GetTenLimitItemSlotArrayNum() == 0)
		return;


	TArray<class UItemSlot*> NoLimitItemSlotArray;
	NoLimitItemSlotArray = RE_GameInstance->GetNoLimitItemSlotArray();

	int32 Row = 0;
	int32 Column = 0;

	for (int32 i = 0; i < NoLimitItemSlotArray.Num(); i++)
	{
		if (!NoLimitItemSlotArray.IsValidIndex(i))
			return;

		UGridSlot* GridSlot = ItemSlot_GridPanel->AddChildToGrid(NoLimitItemSlotArray[i], Row, Column++);
		GridSlot->SetPadding(FMargin(20.f));
		if (Column == 8)
		{
			Row++;
			Column = 0;
		}
	}
}

void URE_ItemInsepctionWidget::SetChildActorClass()
{
	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	int32 FirstItemNum = GameInstance->GetNoLimitSlotArrayFirstItemNum();

	TArray<AActor*> ItemInspectionActor;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UItemSlotInteraction_Interface::StaticClass(), ItemInspectionActor);
	for (AActor* Actor : ItemInspectionActor)
	{
		ItemInspection_Interface = Cast<IItemSlotInteraction_Interface>(Actor);
		ItemInspection_Interface->SetChildActorClassFromPath(FirstItemNum);
	}
}

void URE_ItemInsepctionWidget::InitialSetting()
{
	InitialInputSetting();

	InitializeItemSlot_GridPanel();

	SetChildActorClass();
}






/* Click Event */
void URE_ItemInsepctionWidget::Left_ButtonOnClicked()
{
	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance->GetNoLimitItemSlotArray().Num() == 0)
		return;
	TArray<UItemSlot*> ItemSlotArray = GameInstance->GetNoLimitItemSlotArray();
	
	
	if (ItemNum == 0)
		ItemNum = ItemSlotArray.Num() - 1;
	else
		ItemNum--;
	
	ItemInspection_Interface->SetChildActorClassFromPath(ItemSlotArray[ItemNum]->GetItemNum());
}

void URE_ItemInsepctionWidget::Right_ButtonOnClicked()
{
	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance->GetNoLimitItemSlotArray().Num() == 0)
		return;
	TArray<UItemSlot*> ItemSlotArray = GameInstance->GetNoLimitItemSlotArray();
	
	
	if (ItemNum + 1 == ItemSlotArray.Num())
		ItemNum = 0;
	else
		ItemNum++;
	
	ItemInspection_Interface->SetChildActorClassFromPath(ItemSlotArray[ItemNum]->GetItemNum());
}

