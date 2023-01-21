// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_Telegram.generated.h"

/**
 * 
 */
UCLASS()
class ROOMESCAPE_API URE_Telegram : public UUserWidget
{
	GENERATED_BODY()
	
		virtual bool Initialize();

	UPROPERTY(meta = (BindWidget))
	class UButton* Dialogue_Button_One;

	UPROPERTY(meta = (BindWidget))
	class UButton* Dialogue_Button_Two;

	UPROPERTY(meta = (BindWidget))
	class UButton* Dialogue_Button_Three;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* ContentWidgetSwitcher;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* OK_Button_One;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* OK_Button_Two;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* OK_Button_Three;

	UPROPERTY(EditAnywhere)
	FText Password_One;

	UPROPERTY(EditAnywhere)
	FText Password_Two;

	UPROPERTY(EditAnywhere)
	FText Password_Three;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* Password_EditableText_One;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* Password_EditableText_Two;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* Password_EditableText_Three;

	UPROPERTY(meta = (BindWidget))
	class UButton* Previousbutton_One;

	UPROPERTY(meta = (BindWidget))
	class UButton* Previousbutton_Two;

	UPROPERTY(meta = (BindWidget))
	class UButton* Previousbutton_Three;

	UPROPERTY(meta = (BindWidget))
	class UButton* Previousbutton_Four;

	UPROPERTY(meta = (BindWidget))
	class UButton* Previousbutton_Five;

	UPROPERTY(meta = (BindWidget))
	class UButton* Previousbutton_Six;

	UFUNCTION()
	void Dialogue_Button_One_ButtonOnClicked();

	UFUNCTION()
	void Dialogue_Button_Two_ButtonOnClicked();

	UFUNCTION()
	void Dialogue_Button_Three_ButtonOnClicked();

	/*UFUNCTION()
	void OK_Button_One_OnClicked();

	UFUNCTION()
	void OK_Button_Two_OnClicked();

	UFUNCTION()
	void OK_Button_Three_OnClicked();*/

	UFUNCTION()
	void Previousbutton_One_OnClicked();

	UFUNCTION()
	void Previousbutton_Two_OnClicked();

	UFUNCTION()
	void Previousbutton_Three_OnClicked();

	UFUNCTION()
	void Previousbutton_Four_OnClicked();

	UFUNCTION()
	void Previousbutton_Five_OnClicked();

	UFUNCTION()
	void Previousbutton_Six_OnClicked();






	UPROPERTY(EditAnywhere)
	int32 Chapter_One;

	UPROPERTY(EditAnywhere)
	int32 Quest_One;

	UPROPERTY(EditAnywhere)
	int32 LockNum_One;

	UPROPERTY(EditAnywhere)
	int32 Chapter_Two;

	UPROPERTY(EditAnywhere)
	int32 Quest_Two;

	UPROPERTY(EditAnywhere)
	int32 LockNum_Two;

	UPROPERTY(EditAnywhere)
	int32 Chapter_Three;

	UPROPERTY(EditAnywhere)
	int32 Quest_Three;

	UPROPERTY(EditAnywhere)
	int32 LockNum_Three;


	UPROPERTY(EditAnywhere)
	int32 ItemNum_One = 0;

	UPROPERTY(EditAnywhere)
	int32 ItemNum_Two = 0;

	UPROPERTY(EditAnywhere)
	int32 ItemNum_Three = 0;

	bool bOK_Button_Two_OnClicked = false;





	UFUNCTION()
	void Password_EditableText_One_Commit(const FText& InText, ETextCommit::Type InCommitType);
	UFUNCTION()
	void Password_EditableText_Two_Commit(const FText& InText, ETextCommit::Type InCommitType);
	UFUNCTION()
	void Password_EditableText_Three_Commit(const FText& InText, ETextCommit::Type InCommitType);




	UPROPERTY(meta = (BindWidget))
	class UButton* HomeButton;

	UFUNCTION()
	void HomeButton_ButtonOnClicked();

	UPROPERTY(EditAnywhere)
	int32 HomeWidgetIndex;

	UPROPERTY()
	class URE_PhoneWidget* PhoneWidget;

public:
	void SetParentWidget(class URE_PhoneWidget* ParentWidget);


};
