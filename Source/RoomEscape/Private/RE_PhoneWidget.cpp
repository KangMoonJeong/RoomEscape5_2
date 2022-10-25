// Fill out your copyright notice in the Description page of Project Settings.


#include "RE_PhoneWidget.h"
#include "Components/Button.h"
#include "RoomEscape\RE_PlayerController.h"

bool URE_PhoneWidget::Initialize()
{
	bool Success = UUserWidget::Initialize();
	if (!Success)
		return false;

	TurnOff_Button->OnClicked.AddDynamic(this, &URE_PhoneWidget::TurnOff_ButtonOnClicked);
	TurnOff_Button_1->OnClicked.AddDynamic(this, &URE_PhoneWidget::TurnOff_ButtonOnClicked);
	TurnOff_Button_2->OnClicked.AddDynamic(this, &URE_PhoneWidget::TurnOff_ButtonOnClicked);

	return true;
}

void URE_PhoneWidget::TurnOff_ButtonOnClicked()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;

	RE_PlayerController->OnHUDOffCurrentWidget();
}
