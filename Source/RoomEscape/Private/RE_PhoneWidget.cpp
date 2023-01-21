#include "RE_PhoneWidget.h"
#include "Components/Button.h"
#include "Components\WidgetSwitcher.h"
#include "RE_Telegram.h"
#include "RoomEscape\RE_PlayerController.h"

bool URE_PhoneWidget::Initialize()
{
	bool Success = UUserWidget::Initialize();
	if (!Success)
		return false;

	TurnOff_Button->OnClicked.AddDynamic(this, &URE_PhoneWidget::TurnOff_ButtonOnClicked);
	TurnOff_Button_1->OnClicked.AddDynamic(this, &URE_PhoneWidget::TurnOff_ButtonOnClicked);
	TurnOff_Button_2->OnClicked.AddDynamic(this, &URE_PhoneWidget::TurnOff_ButtonOnClicked);

	YoungerPhone_Button->OnClicked.AddDynamic(this, &URE_PhoneWidget::YoungerPhone_ButtonOnClicked);
	OlderPhone_Button->OnClicked.AddDynamic(this, &URE_PhoneWidget::OlderPhone_ButtonOnClicked);
	HusbandPhone_Button->OnClicked.AddDynamic(this, &URE_PhoneWidget::HusbandPhone_ButtonOnClicked);

	YoungerSis_Telegram_Button->OnClicked.AddDynamic(this, &URE_PhoneWidget::YoungerSis_Telegram_ButtonOnClicked);
	YoungerSis_Diary_Button->OnClicked.AddDynamic(this, &URE_PhoneWidget::YoungerSis_Diary_ButtonOnClicked);
	OlderSis_Telegram_Button->OnClicked.AddDynamic(this, &URE_PhoneWidget::OlderSis_Telegram_ButtonOnClicked);
	OlderSis_Google_Button->OnClicked.AddDynamic(this, &URE_PhoneWidget::OlderSis_Google_ButtonOnClicked);
	OlderSis_Diary_Button->OnClicked.AddDynamic(this, &URE_PhoneWidget::OlderSis_Diary_ButtonOnClicked);
	Husband_Telegram_Button->OnClicked.AddDynamic(this, &URE_PhoneWidget::Husband_Telegram_ButtonOnClicked);


	return true;
}

void URE_PhoneWidget::TurnOff_ButtonOnClicked()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;

	RE_PlayerController->OnHUDOffCurrentWidget();
}

void URE_PhoneWidget::YoungerPhone_ButtonOnClicked()
{
	PhoneWidgetSwitcher->SetActiveWidgetIndex(0);
	CurrentPhoneIndex = 0;
}

void URE_PhoneWidget::OlderPhone_ButtonOnClicked()
{
	PhoneWidgetSwitcher->SetActiveWidgetIndex(1);
	CurrentPhoneIndex = 1;
}

void URE_PhoneWidget::HusbandPhone_ButtonOnClicked()
{
	PhoneWidgetSwitcher->SetActiveWidgetIndex(2);
	CurrentPhoneIndex = 2;
}



void URE_PhoneWidget::YoungerSis_Telegram_ButtonOnClicked()
{
	BP_Telegram_Younger->SetParentWidget(this);
	YoungerSis_Switcher->SetActiveWidgetIndex(1);
}

void URE_PhoneWidget::YoungerSis_Diary_ButtonOnClicked()
{
	BP_Diary_Younger->SetParentWidget(this);
	YoungerSis_Switcher->SetActiveWidgetIndex(2);

}

void URE_PhoneWidget::OlderSis_Telegram_ButtonOnClicked()
{
	BP_Telegram_Older->SetParentWidget(this);
	OlderSis_Switcher->SetActiveWidgetIndex(1);

}
void URE_PhoneWidget::OlderSis_Diary_ButtonOnClicked()
{
	BP_Diary_Older->SetParentWidget(this);
	OlderSis_Switcher->SetActiveWidgetIndex(2);

}

void URE_PhoneWidget::OlderSis_Google_ButtonOnClicked()
{
	BP_Google_Older->SetParentWidget(this);
	OlderSis_Switcher->SetActiveWidgetIndex(3);
}


void URE_PhoneWidget::Husband_Telegram_ButtonOnClicked()
{
	BP_Telegram_Husband->SetParentWidget(this);
	Husband_Switcher->SetActiveWidgetIndex(1);

}

void URE_PhoneWidget::GoHomeWidgetIndex()
{
	if(CurrentPhoneIndex == 0)
		YoungerSis_Switcher->SetActiveWidgetIndex(0);
	else if(CurrentPhoneIndex == 1)
		OlderSis_Switcher->SetActiveWidgetIndex(0);
	else
		Husband_Switcher->SetActiveWidgetIndex(0);
}
