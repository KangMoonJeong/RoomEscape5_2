#include "SettingWidget.h"
#include "Components/Button.h"
#include "RE_PlayerController.h"
#include "Kismet/GamePlayStatics.h"
#include "SaveListWidget.h"


bool USettingWidget::Initialize()
{
	if (Super::Initialize() == false)
	{
		return false;
	}

	X_Button->OnClicked.AddDynamic(this, &USettingWidget::X_ButtonOnClicked);
	SaveLoad_Button->OnClicked.AddDynamic(this, &USettingWidget::SaveLoad_ButtonOnClicked);
	New_Button->OnClicked.AddDynamic(this, &USettingWidget::New_ButtonOnClicked);

	return true;

}

	/* New Button */
void USettingWidget::New_ButtonOnClicked()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (RE_PlayerController)
		RE_PlayerController->DeleteGameData();


	this->RemoveFromViewport();
	UGameplayStatics::OpenLevel(GetWorld(), MapName, true);

}





	/* SaveLoad Button */
void USettingWidget::SaveLoad_ButtonOnClicked()
{
	if (!SaveListWidgetClass)
		return;
	
	SaveListWidget = CreateWidget<USaveListWidget>(this, SaveListWidgetClass);
	SaveListWidget->SetSaveListUnitWidgetIndex(0);
	SaveListWidget->AddToViewport();

}





/* X Button */
void USettingWidget::X_ButtonOnClicked()
{
	
}
