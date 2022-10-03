
#include "RE_LoungeSaveListWidget.h"
#include "Components/Button.h"
#include "Public\RE_LoungeWidgetSaveUnit.h"

bool URE_LoungeSaveListWidget::Initialize()
{
	if (Super::Initialize() == false)
		return false;

	X_Button->OnClicked.AddDynamic(this, &URE_LoungeSaveListWidget::X_ButtonOnClicked);

	return true;
}


/* Widget Switcher Setting */
void URE_LoungeSaveListWidget::SetSaveListUnitWidgetIndex(int32 Set)
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
void URE_LoungeSaveListWidget::X_ButtonOnClicked()
{
	RemoveFromParent();