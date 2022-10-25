#include "VIsiblePasswordWidget.h"
#include "RoomEscape\RE_PlayerController.h"
#include "RoomEscape\RE_GameInstance.h"
#include "Components/Button.h"




bool UVIsiblePasswordWidget::Initialize()
{
	bool Success = UUserWidget::Initialize();
	if (!Success)
		return false;

	X_Button->OnClicked.AddDynamic(this, &UVIsiblePasswordWidget::HiddenWidgetSettig);
	VisibleWidgetSettig();

	return true;
}


void UVIsiblePasswordWidget::VisibleWidgetSettig()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;

	RE_PlayerController->OnCurrentWidgetOffHUD(this, EInputMode::EIM_UIOnly);


}


void UVIsiblePasswordWidget::HiddenWidgetSettig()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;

	RE_PlayerController->OnHUDOffCurrentWidget();

	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
		return;

	GameInstance->GetUnLockedActorNum(Chapter, Quest, LockNum);
}