#include "SaveListWidget.h"
#include "RE_SaveListUnitWidget.h"
#include "Components/Button.h"


bool USaveListWidget::Initialize()
{
	if (Super::Initialize() == false)
		return false;

	X_Button->OnClicked.AddDynamic(this, &USaveListWidget::X_ButtonOnClicked);

	return true;
}


	/* Widget Switcher Setting */
void USaveListWidget::SetSaveListUnitWidgetIndex(int32 Set)
{
	SaveListUnitWidget_1->SetActiveWidgetIndex(Set);
	SaveListUnitWidget_2->SetActiveWidgetIndex(Set);
	SaveListUnitWidget_3->SetActiveWidgetIndex(Set);
	SaveListUnitWidget_4->SetActiveWidgetIndex(Set);
	SaveListUnitWidget_5->SetActiveWidgetIndex(Set);
	SaveListUnitWidget_6->SetActiveWidgetIndex(Set);

	FString Temp = "HighResShot";
	GetOwningPlayer()->ConsoleCommand(Temp);
}






	/* X_Button On Clicked Remove From Parent */
void USaveListWidget::X_ButtonOnClicked()
{
	RemoveFromParent();
}


