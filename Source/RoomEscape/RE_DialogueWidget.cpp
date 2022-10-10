#include "RE_DialogueWidget.h"
#include "Components\Image.h"
#include "Components\TextBlock.h"
#include "Engine\Texture2D.h"
#include "RE_Dialogue.h"
#include "RE_PlayerController.h"
#include "RE_Dialogue_Selection.h"
#include "RE_GameInstance.h"
#include "Components\Button.h"
#include "Kismet/GamePlayStatics.h"



void URE_DialogueWidget::RemoveWidget()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());

	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());


	if (!RE_PlayerController && !GameInstance)
		return;


	CurrentRowNum = 0;
	RE_PlayerController->OnHUDOffCurrentWidget();
	GameInstance->SetLoveCount(LoveCount);
	
	
	if (bLastIndex == true)
	{
		RE_PlayerController->DeleteGameData();
		this->RemoveFromViewport();
		UGameplayStatics::OpenLevel(GetWorld(), MapName, true);
		return;
	}

}

void URE_DialogueWidget::InitializeProperties(FString FileName, int32 SetLoveCount, bool SetLastIndex)
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
	
	LoveCount = SetLoveCount;
	bLastIndex = SetLastIndex;
	
	if (SetLastIndex == true)
	{
		SetLastIndexLow();
	}
	
	InspectNextDialogue();
	SetCurrentlyRow();
}





void URE_DialogueWidget::InitializeData(int32 SetResultLoveCount)
{
	LoveCount = SetResultLoveCount;
}

void URE_DialogueWidget::SetLastIndexLow()
{
	if (LoveCount >= GoodEnding1LoveCount)
	{
		CurrentRowNum = GoodEnding1Low;
	}
	else if (LoveCount >= BadEnding1LoveCount)
	{
		CurrentRowNum = BadEnding1Low;
	}
	else if (LoveCount >= BadEnding2LoveCount)
	{
		CurrentRowNum = BadEnding2Low;
	}
}

int32 URE_DialogueWidget::GetLoveCount()
{
	return LoveCount;
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

	UE_LOG(LogTemp, Warning, TEXT("Before SelectionButton1_OnClicked::LoveCount : %d, ResultLoveCount1 : %d"), LoveCount, (*DialogueRow).ResultLoveCount1);

	CurrentRowNum += (*DialogueRow).ResultSum1;
	LoveCount += (*DialogueRow).ResultLoveCount1;

	UE_LOG(LogTemp, Warning, TEXT("After SelectionButton1_OnClicked::LoveCount : %d, ResultLoveCount1 : %d"), LoveCount, (*DialogueRow).ResultLoveCount1);

}

void URE_DialogueWidget::SelectionButton2_OnClicked()
{
	BP_Dialogue_Selection->SetVisibility(ESlateVisibility::Collapsed);
	VisibleDialogueSelection = false;

	UE_LOG(LogTemp, Warning, TEXT("Before SelectionButton2_OnClicked::LoveCount : %d, ResultLoveCount2 : %d"), LoveCount, (*DialogueRow).ResultLoveCount2);

	CurrentRowNum += (*DialogueRow).ResultSum2;
	LoveCount += (*DialogueRow).ResultLoveCount2;

	UE_LOG(LogTemp, Warning, TEXT("After SelectionButton2_OnClicked::LoveCount : %d, ResultLoveCount2 : %d"), LoveCount, (*DialogueRow).ResultLoveCount2);

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
