#include "StartWidget.h"
#include "Components/Button.h"
#include "Kismet/GamePlayStatics.h"
#include "RE_PlayerController.h"
#include "SaveListWidget.h"


bool UStartWidget::Initialize()
{
	bool Success = UUserWidget::Initialize();
	if (!Success)
		return false;


	NewGame_Button->OnClicked.AddDynamic(this, &UStartWidget::NewGameOnClicked);
	Load_Button->OnClicked.AddDynamic(this, &UStartWidget::LoadOnClicked);
	

	return true;
}





	/* OnClicked New Game Button */
void  UStartWidget::NewGameOnClicked()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (RE_PlayerController)
		RE_PlayerController->DeleteGameData();
	

	this->RemoveFromViewport();
	UGameplayStatics::OpenLevel(GetWorld(), MapName, true);
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




