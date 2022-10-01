#include "RE_DialogueWidget.h"
#include "Components\Image.h"
#include "Components\TextBlock.h"
#include "Engine\Texture2D.h"
#include "RE_Dialogue.h"
#include "RE_PlayerController.h"
#include "RE_Dialogue_Selection.h"
#include "Components\Button.h"



void URE_DialogueWidget::RemoveWidget()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;

	CurrentRowNum = 0;
	
	RE_PlayerController->OnHUDOffCurrentWidget();
}

void URE_DialogueWidget::InitializeProperties(FString FileName)
{
	if (*FileName == FString(""))
		return;

	TestDataTable = LoadObject<UDataTable>(NULL, *FileName);
	if (!TestDataTable)
		return;

	BP_Dialogue_Selection->SelectionButton1->OnClicked.AddDynamic(this, &URE_DialogueWidget::SelectionButton1_OnClicked);
	BP_Dialogue_Selection->SelectionButton2->OnClicked.AddDynamic(this, &URE_DialogueWidget::SelectionButton2_OnClicked);




	HasNextDialogue = true;
	bIsFocusable = true;
	SetKeyboardFocus();

	InspectNextDialogue();
	SetCurrentlyRow();
}





/* 일반 대사*/
void URE_DialogueWidget::FindCurrentRowNum()
{
	CurrentRowNum += (*DialogueRow).Sum;
}

void URE_DialogueWidget::InspectNextDialogue()
{
	DialogueRow = TestDataTable->FindRow<FRE_Dialogue>(FName(*(FString::FormatAsNumber(CurrentRowNum))), FString(""));

	if (!DialogueRow)
	{
		RemoveWidget();
		HasNextDialogue = false;
		return;
	}
	
}

void URE_DialogueWidget::SetCurrentlyRow()
{

	Character_Image->SetBrushFromTexture(CharacterImageArray[(*DialogueRow).CharacterImage]);
	CharacterName_Text->SetText((*DialogueRow).CharacterName);
	Dialogue_Text->SetText((*DialogueRow).Dialogue);

	InspectDialogueSelectBool();

}





/* 선택지 */
void URE_DialogueWidget::InspectDialogueSelectBool()
{
	if ((*DialogueRow).SelectBool != 1)
		return;

	VisibleDialogueSelection = true;
	BP_Dialogue_Selection->SetVisibility(ESlateVisibility::Visible);

	SetSelectionDialogueCurrentlyRow();

}

void URE_DialogueWidget::SetSelectionDialogueCurrentlyRow()
{
	BP_Dialogue_Selection->SelectionText1->SetText((*DialogueRow).SelectDialogue1);
	BP_Dialogue_Selection->SelectionText2->SetText((*DialogueRow).SelectDialogue2);

}

void URE_DialogueWidget::SelectionButton1_OnClicked()
{
	BP_Dialogue_Selection->SetVisibility(ESlateVisibility::Collapsed);
	VisibleDialogueSelection = false;

	CurrentRowNum += (*DialogueRow).ResultSum1;

}

void URE_DialogueWidget::SelectionButton2_OnClicked()
{
	BP_Dialogue_Selection->SetVisibility(ESlateVisibility::Collapsed);
	VisibleDialogueSelection = false;

	CurrentRowNum += (*DialogueRow).ResultSum2;

}







FReply URE_DialogueWidget::NativeOnKeyDown(const FGeometry & InGeometry, const FKeyEvent & InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	
	
	if(VisibleDialogueSelection)
		return FReply::Handled();

	FindCurrentRowNum();
	InspectNextDialogue();

	// 위 아래가 원래 하나의 함수였는데 분리시켜놔서 이거 꼭 써줘야함
	if(!HasNextDialogue)
		return FReply::Handled();


	SetCurrentlyRow();



	return FReply::Handled();
}
