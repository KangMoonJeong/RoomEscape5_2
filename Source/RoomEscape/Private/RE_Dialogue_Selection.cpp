#include "RE_Dialogue_Selection.h"
#include "Components\Button.h"
#include "Components\TextBlock.h"

bool URE_Dialogue_Selection::Initialize()
{
	bool Success = UUserWidget::Initialize();
	if (!Success)
		return false;

	SelectionButton1->OnClicked.AddDynamic(this, &URE_Dialogue_Selection::SelectionButton1_OnClicked);
	SelectionButton2->OnClicked.AddDynamic(this, &URE_Dialogue_Selection::SelectionButton2_OnClicked);

	return true;
}


//void URE_Dialogue_Selection::SelectionButton1_OnClicked()
//{
//	UE_LOG(LogTemp, Warning, TEXT("URE_Dialogue_Selection::SelectionButton1_OnClicked()"));
//	SetVisibility(ESlateVisibility::Collapsed);
//}
//
//void URE_Dialogue_Selection::SelectionButton2_OnClicked()
//{
//	UE_LOG(LogTemp, Warning, TEXT("URE_Dialogue_Selection::SelectionButton2_OnClicked()"));
//	SetVisibility(ESlateVisibility::Collapsed);
//
//}
