#include "PasswordWidget.h"
#include "Components/Button.h"
#include "RE_PlayerController.h"

bool UPasswordWidget::Initialize()
{
	bool Success = UUserWidget::Initialize();
	if (!Success)
		return false;

	VisibleWidgetSettig();

	return true;
}

void UPasswordWidget::VisibleWidgetSettig()
{


	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;

	RE_PlayerController->OnCurrentWidgetOffHUD(this, EInputMode::EIM_UIOnly);
}

void UPasswordWidget::HidenWidgetSettig()
{

	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;

	RE_PlayerController->OnHUDOffCurrentWidget();
}


void UPasswordWidget::CorrectPassword()
{
	UE_LOG(LogTemp, Warning, TEXT("UPasswordWidget::CorrectPassword()"))

}

