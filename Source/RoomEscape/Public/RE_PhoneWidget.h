// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_PhoneWidget.generated.h"

/**
 * 
 */
UCLASS()
class ROOMESCAPE_API URE_PhoneWidget : public UUserWidget
{
	GENERATED_BODY()
	

	virtual bool Initialize();


	UPROPERTY(meta = (BindWidget))
	class UButton* TurnOff_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* TurnOff_Button_1;

	UPROPERTY(meta = (BindWidget))
	class UButton* TurnOff_Button_2;

	UFUNCTION()
	void TurnOff_ButtonOnClicked();

};
