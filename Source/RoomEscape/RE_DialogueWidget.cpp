#include "RE_DialogueWidget.h"
#include "Components\Image.h"
#include "Components\TextBlock.h"
#include "Engine\Texture2D.h"
#include "RE_Dialogue.h"
#include "RE_PlayerController.h"
#include "RE_Dialogue_Selection.h"



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

	HasNextDialogue = true;
	bIsFocusable = true;
	SetKeyboardFocus();
	InspectNextDialogue();
	SetCurrentlyRow();
}








void URE_DialogueWidget::InspectDialogueSelectBool()
{
	if ((*DialogueRow).SelectBool != 1)
		return;

	UE_LOG(LogTemp, Warning, TEXT("if ((*DialogueRow).SelectBool)"));
	VisibleDialogueSelection = true;
	BP_Dialogue_Selection->SetVisibility(ESlateVisibility::Visible);


}

void URE_DialogueWidget::InspectNextDialogue()
{
	CurrentRowNum++;
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

}


FReply URE_DialogueWidget::NativeOnKeyDown(const FGeometry & InGeometry, const FKeyEvent & InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	
	InspectDialogueSelectBool();
	
	if(VisibleDialogueSelection)
		return FReply::Handled();


	InspectNextDialogue();

	if(!HasNextDialogue)
		return FReply::Handled();


	SetCurrentlyRow();



	return FReply::Handled();
}
