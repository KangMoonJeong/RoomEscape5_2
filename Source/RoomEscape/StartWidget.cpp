#include "StartWidget.h"
#include "Components/Button.h"
#include "Kismet/GamePlayStatics.h"
#include "RE_PlayerController.h"
#include "SaveListWidget.h"
#include "Kismet\KismetSystemLibrary.h"
#include "RoomEscape\RE_GameInstance.h"
#include"Components\ComboBoxString.h"
#include "RE_WidgetSaveGame.h"
#include "Kismet\KismetInternationalizationLibrary.h"
#include "Kismet\KismetSystemLibrary.h"


bool UStartWidget::Initialize()
{
	bool Success = UUserWidget::Initialize();
	if (!Success)
		return false;


	NewGame_Button->OnClicked.AddDynamic(this, &UStartWidget::NewGameOnClicked);
	Load_Button->OnClicked.AddDynamic(this, &UStartWidget::LoadOnClicked);
	Exit_Button->OnClicked.AddDynamic(this, &UStartWidget::Exit_ButtonOnClicked);

	return true;
}




	/* OnClicked New Game Button */
void  UStartWidget::NewGameOnClicked()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (RE_PlayerController)
		RE_PlayerController->DeleteGameData();
	
	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	GameInstance->SmoothLoadLevel(MapName);

	this->RemoveFromViewport();
	//UGameplayStatics::OpenLevel(GetWorld(), MapName, true);
}





	/* OnClicked Load Game Button */
void UStartWidget::LoadOnClicked()
{
	if (!SaveListWidgetClass)
		return;

	SaveListWidget = CreateWidget<USaveListWidget>(this, SaveListWidgetClass);
	SaveListWidget->SetSaveListUnitWidgetIndex(1);
	SaveListWidget->AddToViewport();
}

void UStartWidget::Exit_ButtonOnClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UUserWidget::GetOwningPlayer(), EQuitPreference::Quit, false);
}





void UStartWidget::InitialLocalComboBox()
{
	LoadLocalStringFromSaveGame();
	
	if (LocalString == FString("None"))
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("if (LocalString == FString(None))"));

		Local_ComboBox->SetSelectedOption("en");
		UKismetInternationalizationLibrary::SetCurrentCulture("en");
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("!!!!!!!!!if (LocalString == FString(None))"));

		Local_ComboBox->SetSelectedOption(LocalString);
		UKismetInternationalizationLibrary::SetCurrentCulture(LocalString);
	}
}



void UStartWidget::SaveLocalString()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;
	
	RE_PlayerController->SetLocalString(LocalString);
}

void UStartWidget::SetLocalString(FString SetLocalString)
{
	LocalString = SetLocalString;
}

void UStartWidget::LoadLocalStringFromSaveGame()
{
	//URE_WidgetSaveGame* SaveGame = Cast<URE_WidgetSaveGame>(UGameplayStatics::CreateSaveGameObject(URE_WidgetSaveGame::StaticClass()));
	//if (UGameplayStatics::DoesSaveGameExist("MasterSlot", 0))
	//{
	//	SaveGame = Cast<URE_WidgetSaveGame>(UGameplayStatics::LoadGameFromSlot("MasterSlot", 0));
	//	//LocalString = SaveGame->LocalString;
	//}
}

void UStartWidget::SaveLocalStringToSaveGame()
{
	URE_WidgetSaveGame* SaveGame = Cast<URE_WidgetSaveGame>(UGameplayStatics::CreateSaveGameObject(URE_WidgetSaveGame::StaticClass()));

	//UKismetSystemLibrary::PrintString(GetWorld(), "if (UGameplayStatics::DoesSaveGameExist(MasterSlot, 0))");
	SaveGame = Cast<URE_WidgetSaveGame>(UGameplayStatics::LoadGameFromSlot("MasterSlot", 0));
	SaveGame->LocalString = LocalString;

	UGameplayStatics::SaveGameToSlot(SaveGame, "MasterSlot", 0);

	//if (UGameplayStatics::DoesSaveGameExist("MasterSlot", 0))
	//{
	//	UKismetSystemLibrary::PrintString(GetWorld(), "if (UGameplayStatics::DoesSaveGameExist(MasterSlot, 0))");
	//	SaveGame = Cast<URE_WidgetSaveGame>(UGameplayStatics::LoadGameFromSlot("MasterSlot", 0));
	////	SaveGame->LocalString = LocalString;
	//}
	//else
	//{
	//	UKismetSystemLibrary::PrintString(GetWorld(), "!!!!!!!!!!! if (UGameplayStatics::DoesSaveGameExist(MasterSlot, 0))");

	//}

	//SaveGame->LocalString = LocalString;

	//UGameplayStatics::SaveGameToSlot(SaveGame, "MasterSlot", 0);

}




