#include "RE_CameraInspectionWidget.h"
#include "Inspection_Interface.h"
#include "ItemSlotInteraction_Interface.h"
#include "RE_GameInstance.h"
#include "ItemSlot.h"
#include "RE_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components\GridPanel.h"
#include "Components\GridSlot.h"
#include "Components/Button.h"
#include "Components\UniformGridPanel.h"



bool URE_CameraInspectionWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
		return false;


	Left_Button->OnClicked.AddDynamic(this, &URE_CameraInspectionWidget::Left_ButtonOnClicked);
	Right_Button->OnClicked.AddDynamic(this, &URE_CameraInspectionWidget::Right_ButtonOnClicked);


	return true;
}


void URE_CameraInspectionWidget::InitialInputSetting()
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

void URE_CameraInspectionWidget::SetChildActorClass()
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


void URE_CameraInspectionWidget::InitializeItemSlot_GridPanel()
{
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (RE_GameInstance->GetTenLimitItemSlotArrayNum() == 0)
		return;


	TArray<class UItemSlot*> NoLimitItemSlotArray;
	NoLimitItemSlotArray = RE_GameInstance->GetNoLimitItemSlotArray();

	int32 Row = 0;
	int32 Column = 0;

	UE_LOG(LogTemp, Warning, TEXT("URE_CameraInspectionWidget: :NoLimitItemSlotArray.Num() : %d"), NoLimitItemSlotArray.Num());


	for (int32 i = 0; i < NoLimitItemSlotArray.Num(); i++)
	{
		if (!NoLimitItemSlotArray[i]->IsValidLowLevel())
		{
			UE_LOG(LogTemp, Warning, TEXT("if (!NoLimitItemSlotArray[i]->IsValidLowLevel()) : %d"), i);
			continue;
		}

		UUserWidget* ItemSlot = NoLimitItemSlotArray[i];
		ItemSlot_UniformGridPanel->AddChildToUniformGrid(ItemSlot, Row, Column);

		Column++;
		if (Column == 8)
		{
			Row++;
			Column = 0;
		}
	}
}

void URE_CameraInspectionWidget::InitialSetting()
{
	InitialInputSetting();

	InitializeItemSlot_GridPanel();

	SetChildActorClass();
}






void URE_CameraInspectionWidget::Left_ButtonOnClicked()
{
	TArray<UItemSlot*> ItemSlotArray = UpdateItemSlotArray();
	if (ItemSlotArray.Num() == 0)
		return;



	if (ItemNum <= 0)
		ItemNum = ItemSlotArray.Num() - 1;
	else
		ItemNum--;

	ItemInspection_Interface->SetChildActorClassFromPath(ItemSlotArray[ItemNum]->GetItemNum());
}

void URE_CameraInspectionWidget::Right_ButtonOnClicked()
{
	TArray<UItemSlot*> ItemSlotArray = UpdateItemSlotArray();
	if (ItemSlotArray.Num() == 0)
		return;



	if (ItemNum + 1 >= ItemSlotArray.Num())
		ItemNum = 0;
	else
		ItemNum++;

	ItemInspection_Interface->SetChildActorClassFromPath(ItemSlotArray[ItemNum]->GetItemNum());
}







void URE_CameraInspectionWidget::ReLocationItemSlot_GridPanel()
{
	ItemSlot_UniformGridPanel->ClearChildren();
	InitializeItemSlot_GridPanel();
}

void URE_CameraInspectionWidget::SetSpawnActorFromPath(int32 PathNum)
{
	ItemInspection_Interface->SetChildActorClassFromPath(PathNum);


	TArray<UItemSlot*> ItemSlotArray = UpdateItemSlotArray();
	if (ItemSlotArray.Num() == 0)
		return;


	int32 i = 0;
	for (auto& Elem : ItemSlotArray)
	{
		if (Elem->GetItemNum() == PathNum)
			break;
		i++;
	}
	ItemNum = i;
}


TArray<UItemSlot*> URE_CameraInspectionWidget::UpdateItemSlotArray()
{
	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
		return GameInstance->GetNoLimitItemSlotArray();
}

