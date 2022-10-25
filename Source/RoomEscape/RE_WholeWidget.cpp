#include "RE_WholeWidget.h"
#include "Components/Button.h"
#include "Components\WidgetSwitcher.h"
#include "RE_PlayerController.h"
#include "RE_InventoryWidget.h"
#include "RE_ItemInsepctionWidget.h"
#include "RE_CombineWidget.h"
#include "Kismet\GameplayStatics.h"
#include "Inspection_Interface.h"
#include "GameFramework\Character.h"
#include "FP_FirstPerson/FP_FirstPersonCharacter.h"
#include "RE_CameraInspectionWidget.h"


bool URE_WholeWidget::Initialize()
{
	bool Success = UUserWidget::Initialize();
	if (!Success)
		return false;


	Lounge_Button->OnClicked.AddDynamic(this, &URE_WholeWidget::Lounge_ButtonOnClicked);
	Inventory_Button->OnClicked.AddDynamic(this, &URE_WholeWidget::Inventory_ButtonOnClicked);
	//Inspection_Button->OnClicked.AddDynamic(this, &URE_WholeWidget::Inspection_ButtonOnClicked);
	Combine_Button->OnClicked.AddDynamic(this, &URE_WholeWidget::Combine_ButtonOnClicked);

	X_Button->OnClicked.AddDynamic(this, &URE_WholeWidget::X_ButtonOnClicked);


	return true;
}



void URE_WholeWidget::X_ButtonOnClicked()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;
	RE_PlayerController->OnHUDOffCurrentWidget();
	RE_PlayerController->GetHUDInitializeSlotBar();


	TArray<AActor*> InterfaceActor;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInspection_Interface::StaticClass(), InterfaceActor);
	for (AActor* Actor : InterfaceActor)
	{
		IInspection_Interface* Inspection_Interface = Cast<IInspection_Interface>(Actor);
		Inspection_Interface->ClearInteractionSetting();
	}
	FirstItemInspectionWidgetOpen = true;
}





/* Select Tab */
void URE_WholeWidget::Lounge_ButtonOnClicked()
{
	Content_WidgetSwitcher->SetActiveWidgetIndex(0);
	CurrentWidget = nullptr;
}

void URE_WholeWidget::Inventory_ButtonOnClicked()
{
	if (CurrentWidget == BP_InventoryWidget)
		return;

	CurrentWidget = BP_InventoryWidget;
	Content_WidgetSwitcher->SetActiveWidgetIndex(1);
	BP_InventoryWidget->InitializeData();

}

//void URE_WholeWidget::Inspection_ButtonOnClicked()
//{
//	//if (CurrentWidget == BP_CameraInspectionWidget)
//	//	return;
//
//	//CurrentWidget = BP_CameraInspectionWidget;
//	//Content_WidgetSwitcher->SetActiveWidgetIndex(2);
//
//	//if (FirstItemInspectionWidgetOpen)
//	//{
//	//	BP_CameraInspectionWidget->InitialSetting();
//	//	FirstItemInspectionWidgetOpen = false;
//	//}
//	//else
//	//{
//	//	BP_CameraInspectionWidget->ReLocationItemSlot_GridPanel();
//	//}
//
//}

void URE_WholeWidget::Combine_ButtonOnClicked()
{
	if (CurrentWidget == BP_CombineWidget)
		return;

	CurrentWidget = BP_CombineWidget;
	Content_WidgetSwitcher->SetActiveWidgetIndex(3);


	if (FirstCombineWidgetOpen)
	{
		BP_CombineWidget->InitialSetting();
		FirstCombineWidgetOpen = false;
	}
	else
	{
		BP_CombineWidget->ReLocationItemSlot_GridPanel();
	}

}






void URE_WholeWidget::RelocationInspectionGridPanel()
{
	if (CurrentWidget != BP_CameraInspectionWidget)
		return;

	BP_CameraInspectionWidget->ReLocationItemSlot_GridPanel();
}

void URE_WholeWidget::SetItemInspectionPath(int32 PathNum)
{
	if (CurrentWidget != BP_CameraInspectionWidget)
		return;

	BP_CameraInspectionWidget->SetSpawnActorFromPath(PathNum);
}
