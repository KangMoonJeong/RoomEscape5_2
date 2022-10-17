#include "RE_LoungeWidget.h"
#include "Components/Button.h"
#include "Components\WidgetSwitcher.h"
#include "RE_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet\KismetSystemLibrary.h"


bool URE_LoungeWidget::Initialize()
{
	bool Success = UUserWidget::Initialize();
	if (!Success)
		return false;

	New_Button->OnClicked.AddDynamic(this, &URE_LoungeWidget::New_ButtonOnClicked);
	Storage_Button->OnClicked.AddDynamic(this, &URE_LoungeWidget::Storage_ButtonOnClicked);
	//Sound_Button->OnClicked.AddDynamic(this, &URE_LoungeWidget::Sound_ButtonOnClicked);
	Exit_Button->OnClicked.AddDynamic(this, &URE_LoungeWidget::Exit_ButtonOnClicked);
	NewYes_Button->OnClicked.AddDynamic(this, &URE_LoungeWidget::NewYes_ButtonOnClicked);
	NewNo_Button->OnClicked.AddDynamic(this, &URE_LoungeWidget::NewNo_ButtonOnClicked);
	ExitYes_Button->OnClicked.AddDynamic(this, &URE_LoungeWidget::ExitYes_ButtonOnClicked);
	ExitNo_Button->OnClicked.AddDynamic(this, &URE_LoungeWidget::ExitNo_ButtonOnClicked);
	StorageNo_Button->OnClicked.AddDynamic(this, &URE_LoungeWidget::StorageNo_ButtonOnClicked);


	return true;
}






/* DetailContent_Switcher */
void URE_LoungeWidget::New_ButtonOnClicked()
{
	DetailContent_Switcher->SetActiveWidgetIndex(NewWidgetIndex);
}

void URE_LoungeWidget::Storage_ButtonOnClicked()
{
	DetailContent_Switcher->SetActiveWidgetIndex(StorageWidgetIndex);
}


void URE_LoungeWidget::Exit_ButtonOnClicked()
{
	DetailContent_Switcher->SetActiveWidgetIndex(ExitWidgetIndex);
}






void URE_LoungeWidget::NewYes_ButtonOnClicked()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (RE_PlayerController)
		RE_PlayerController->DeleteGameData();


	this->RemoveFromViewport();
	UGameplayStatics::OpenLevel(GetWorld(), MapName, true);
}

void URE_LoungeWidget::NewNo_ButtonOnClicked()
{
	DetailContent_Switcher->SetActiveWidgetIndex(SettingWidgetIndex);
}

void URE_LoungeWidget::ExitYes_ButtonOnClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UUserWidget::GetOwningPlayer(), EQuitPreference::Quit, false);
}

void URE_LoungeWidget::ExitNo_ButtonOnClicked()
{
	DetailContent_Switcher->SetActiveWidgetIndex(SettingWidgetIndex);

}

void URE_LoungeWidget::StorageNo_ButtonOnClicked()
{
	DetailContent_Switcher->SetActiveWidgetIndex(SettingWidgetIndex);

}
