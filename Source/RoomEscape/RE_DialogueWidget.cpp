#include "RE_DialogueWidget.h"
#include "Components\Image.h"
#include "Components\TextBlock.h"
#include "Engine\Texture2D.h"
#include "RE_Dialogue.h"
#include "RE_PlayerController.h"



void URE_DialogueWidget::RemoveWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("tesfd"));
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;

	CurrentRowNum = 0;
	
	RE_PlayerController->OnHUDOffCurrentWidget();
}





void URE_DialogueWidget::SetCurrentlyRow()
{
	CurrentRowNum++;
	FRE_Dialogue* DialogueRow = TestDataTable->FindRow<FRE_Dialogue>(FName(*(FString::FormatAsNumber(CurrentRowNum))), FString(""));

	if (!DialogueRow)
	{
		RemoveWidget();
		return;
	}

	Character_Image->SetBrushFromTexture(CharacterImageArray[(*DialogueRow).CharacterImage]);
	CharacterName_Text->SetText((*DialogueRow).CharacterName);
	Dialogue_Text->SetText((*DialogueRow).Dialogue);

}


void URE_DialogueWidget::InitializeProperties(FString FileName)
{
	if (*FileName == FString(""))
		return;

	TestDataTable = LoadObject<UDataTable>(NULL, *FileName);
	if (!TestDataTable)
		return;

	bIsFocusable = true;
	SetKeyboardFocus();
	SetCurrentlyRow();
}

FReply URE_DialogueWidget::NativeOnKeyDown(const FGeometry & InGeometry, const FKeyEvent & InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	SetCurrentlyRow();

	return FReply::Handled();
}
