#include "RE_SaveListUnitWidget.h"
#include "Components\WidgetSwitcher.h"
#include "Components\Button.h"
#include "Components\Image.h"
#include "Components\TextBlock.h"
#include "RE_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "RE_SaveGame.h"
#include "Engine\Texture2D.h"


bool URE_SaveListUnitWidget::Initialize()
{
	if (!Super::Initialize())
		return false;

	SetSaveStatus();

	SaveLoad_SaveButton->OnClicked.AddDynamic(this, &URE_SaveListUnitWidget::SaveToSlot);
	SaveLoad_LoadButton->OnClicked.AddDynamic(this, &URE_SaveListUnitWidget::LoadToSlot);
	Load_LoadButton->OnClicked.AddDynamic(this, &URE_SaveListUnitWidget::LoadToSlot);

	return true;
}







/* Save and Load */
URE_SaveGame * URE_SaveListUnitWidget::GetMasterSlot()
{
	URE_SaveGame* MasterSlot = Cast<URE_SaveGame>(UGameplayStatics::CreateSaveGameObject(URE_SaveGame::StaticClass()));

	if (UGameplayStatics::DoesSaveGameExist("MasterSlot", 0))
		MasterSlot = Cast<URE_SaveGame>(UGameplayStatics::LoadGameFromSlot("MasterSlot", 0));

	return MasterSlot;
}

void URE_SaveListUnitWidget::SaveSelectedSlotIndex(int32 SetSlotIndex)
{
	URE_SaveGame* MasterSlot = GetMasterSlot();

	MasterSlot->SelectedSlotIndex = SetSlotIndex;

	UGameplayStatics::SaveGameToSlot(MasterSlot, "MasterSlot", 0);
}

void URE_SaveListUnitWidget::SaveToSlot()
{
	SaveSelectedSlotIndex(SlotIndex);

	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!RE_PlayerController)
		return;

	RE_PlayerController->SaveGameData();
	SetSaveStatus();

}

void URE_SaveListUnitWidget::LoadToSlot()
{
	SaveSelectedSlotIndex(SlotIndex);
	

	UGameplayStatics::OpenLevel(GetWorld(), MapName, true);
}

void URE_SaveListUnitWidget::SetSaveStatus()
{
	URE_SaveGame* MasterSlot = GetMasterSlot();

	if (UGameplayStatics::DoesSaveGameExist(MasterSlot->SlotArray[this->SlotIndex], 0))
	{
		SaveStatusText->SetText(FText::FromString("Saved"));
		SavedImage->SetBrushFromTexture(SavedImageArray[MasterSlot->SavedSlotImageIndex[this->SlotIndex]]);
		if (LoadChapterStatusFromSlot())
		{
			#define LOCTEXT_NAMESPACE "MyNamespace"
			SaveStatusText->SetText(FText::Format(LOCTEXT("", "{0} / {1}"), FText::AsNumber(Chapter), FText::AsNumber(Quest)));
			SavedImage->SetBrushFromTexture(SavedImageArray[MasterSlot->SavedSlotImageIndex[this->SlotIndex]]);
			#undef LOCTEXT_NAMESPACE
		}
	}
}

bool URE_SaveListUnitWidget::LoadChapterStatusFromSlot()
{

	URE_SaveGame* SaveGame = Cast<URE_SaveGame>(UGameplayStatics::CreateSaveGameObject(URE_SaveGame::StaticClass()));

	// 게임 데이터 세이브나 로드시
	if (UGameplayStatics::DoesSaveGameExist("MasterSlot", 0))
	{

		SaveGame = Cast<URE_SaveGame>(UGameplayStatics::LoadGameFromSlot("MasterSlot", 0));


		if (UGameplayStatics::DoesSaveGameExist(SaveGame->SlotArray[SlotIndex], 0))
		{
			SaveGame = Cast<URE_SaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGame->SlotArray[this->SlotIndex], 0));
			Chapter = SaveGame->CurrentChpaterIndex;
			Quest = SaveGame->CurrentQuestIndex;
			return true;
		}
	}
	return false;
}





/* Mouse Enter and Leave */
void URE_SaveListUnitWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	URE_SaveGame* MasterSlot = GetMasterSlot();

	if (UGameplayStatics::DoesSaveGameExist(MasterSlot->SlotArray[this->SlotIndex], 0))
	{
		OpacityImage->SetVisibility(ESlateVisibility::Visible);
		SaveLoadWidgetSwitcher->SetVisibility(ESlateVisibility::Visible);
	}
}

void URE_SaveListUnitWidget::NativeOnMouseLeave(const FPointerEvent & InMouseEvent)
{
	OpacityImage->SetVisibility(ESlateVisibility::Hidden);
	SaveLoadWidgetSwitcher->SetVisibility(ESlateVisibility::Hidden);
}





	/* Widget Switcher */
void URE_SaveListUnitWidget::SetActiveWidgetIndex(int Set)
{
	SaveLoadWidgetSwitcher->SetActiveWidgetIndex(Set);
}
