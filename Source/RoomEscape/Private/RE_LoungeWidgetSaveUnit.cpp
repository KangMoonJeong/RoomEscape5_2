#include "RE_LoungeWidgetSaveUnit.h"

#include "Components\WidgetSwitcher.h"
#include "Components\Button.h"
#include "Components\Image.h"
#include "Components\TextBlock.h"
#include "RE_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "RE_SaveGame.h"
#include "Engine\Texture2D.h"


bool URE_LoungeWidgetSaveUnit::Initialize()
{
	if (!Super::Initialize())
		return false;

	SetSaveStatus();

	SaveLoad_SaveButton->OnClicked.AddDynamic(this, &URE_LoungeWidgetSaveUnit::SaveToSlot);
	SaveLoad_LoadButton->OnClicked.AddDynamic(this, &URE_LoungeWidgetSaveUnit::LoadToSlot);
	Load_LoadButton->OnClicked.AddDynamic(this, &URE_LoungeWidgetSaveUnit::LoadToSlot);

	return true;
}







/* Save and Load */
URE_SaveGame* URE_LoungeWidgetSaveUnit::GetMasterSlot()
{
	URE_SaveGame* MasterSlot = Cast<URE_SaveGame>(UGameplayStatics::CreateSaveGameObject(URE_SaveGame::StaticClass()));

	if (UGameplayStatics::DoesSaveGameExist("MasterSlot", 0))
		MasterSlot = Cast<URE_SaveGame>(UGameplayStatics::LoadGameFromSlot("MasterSlot", 0));

	return MasterSlot;
}

void URE_LoungeWidgetSaveUnit::SaveSelectedSlotIndex(int32 SetSlotIndex)
{
	URE_SaveGame* MasterSlot = GetMasterSlot();

	MasterSlot->SelectedSlotIndex = SetSlotIndex;

	UGameplayStatics::SaveGameToSlot(MasterSlot, "MasterSlot", 0);
}

void URE_LoungeWidgetSaveUnit::SaveToSlot()
{
	SaveSelectedSlotIndex(SlotIndex);

	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!RE_PlayerController)
		return;

	RE_PlayerController->SaveGameData();
	SetSaveStatus();

}

void URE_LoungeWidgetSaveUnit::LoadToSlot()
{
	SaveSelectedSlotIndex(SlotIndex);

	UGameplayStatics::OpenLevel(GetWorld(), MapName, true);
}

void URE_LoungeWidgetSaveUnit::SetSaveStatus()
{
	URE_SaveGame* MasterSlot = GetMasterSlot();

	if (UGameplayStatics::DoesSaveGameExist(MasterSlot->SlotArray[this->SlotIndex], 0))
	{
		SaveStatusText->SetText(FText::FromString("Saved"));
		SavedImage->SetBrushFromTexture(SavedImageArray[MasterSlot->SavedSlotImageIndex[this->SlotIndex]]);
	}
}






/* Mouse Enter and Leave */
void URE_LoungeWidgetSaveUnit::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	URE_SaveGame* MasterSlot = GetMasterSlot();

	if (UGameplayStatics::DoesSaveGameExist(MasterSlot->SlotArray[this->SlotIndex], 0))
	{
		OpacityImage->SetVisibility(ESlateVisibility::Visible);
		SaveLoadWidgetSwitcher->SetVisibility(ESlateVisibility::Visible);
	}
}

void URE_LoungeWidgetSaveUnit::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	OpacityImage->SetVisibility(ESlateVisibility::Hidden);
	SaveLoadWidgetSwitcher->SetVisibility(ESlateVisibility::Hidden);
}





/* Widget Switcher */
void URE_LoungeWidgetSaveUnit::SetActiveWidgetIndex(int Set)
{
	SaveLoadWidgetSwitcher->SetActiveWidgetIndex(Set);
}
