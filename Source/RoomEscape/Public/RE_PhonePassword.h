// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_PhonePassword.generated.h"

/**
 * 
 */
UCLASS()
class ROOMESCAPE_API URE_PhonePassword : public UUserWidget
{
	GENERATED_BODY()


	virtual bool Initialize();

public:
	UPROPERTY(meta = (BindWidget))
	class UEditableText* Password_EditableText;


	UPROPERTY(meta = (BindWidget))
	class UButton* OK_Button;

	UPROPERTY(EditAnywhere)
	FText Password;

	UPROPERTY(meta = (BindWidget))
	class UImage* UnLockedImage;

	UPROPERTY(EditAnywhere)
	class UTexture2D* TextureArray;

	UFUNCTION()
	void OK_Button_OnClicked();


	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* Password_WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UButton* Previousbutton;

	UPROPERTY(meta = (BindWidget))
	class UButton* Removebutton;

	UFUNCTION()
	void Previousbutton_ButtonOnClicked();

	UFUNCTION()
	void Removebutton_ButtonOnClicked();

};
