#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_PhoneWidget.generated.h"


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





	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* PhoneWidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UButton* YoungerPhone_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* OlderPhone_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* HusbandPhone_Button;

	UPROPERTY()
	int32 CurrentPhoneIndex = 0;

	UFUNCTION()
	void YoungerPhone_ButtonOnClicked();

	UFUNCTION()
	void OlderPhone_ButtonOnClicked();

	UFUNCTION()
	void HusbandPhone_ButtonOnClicked();



	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* YoungerSis_Switcher;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* OlderSis_Switcher;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* Husband_Switcher;



	UPROPERTY(meta = (BindWidget))
	class URE_Telegram* BP_Telegram_Younger;

	UPROPERTY(meta = (BindWidget))
	class URE_Telegram* BP_Diary_Younger;

	UPROPERTY(meta = (BindWidget))
	class URE_Telegram* BP_Telegram_Older;

	UPROPERTY(meta = (BindWidget))
	class URE_Telegram* BP_Diary_Older;

	UPROPERTY(meta = (BindWidget))
	class URE_Telegram* BP_Google_Older;

	UPROPERTY(meta = (BindWidget))
	class URE_Telegram* BP_Telegram_Husband;




	UPROPERTY(meta = (BindWidget))
	class UButton* YoungerSis_Telegram_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* YoungerSis_Diary_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* OlderSis_Telegram_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* OlderSis_Google_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* OlderSis_Diary_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* Husband_Telegram_Button;

	UFUNCTION()
	void YoungerSis_Telegram_ButtonOnClicked();

	UFUNCTION()
	void YoungerSis_Diary_ButtonOnClicked();

	UFUNCTION()
	void OlderSis_Telegram_ButtonOnClicked();

	UFUNCTION()
	void OlderSis_Google_ButtonOnClicked();

	UFUNCTION()
	void OlderSis_Diary_ButtonOnClicked();

	UFUNCTION()
	void Husband_Telegram_ButtonOnClicked();


	
public:
	UFUNCTION()
	void GoHomeWidgetIndex();


	void SetSolvedQuestNum(int32 SetItemNum, int32 SetChapterNum, int32 SetQuestNum, int32 SetLockNum);
	void SetSolvedQuest();


	UPROPERTY()
	bool bSolvedPassword = false;

	UPROPERTY()
	int32 ItemNum = 0;

	UPROPERTY()
	int32 ChapterNum = 0;

	UPROPERTY()
	int32 QuestNum = 0;

	UPROPERTY()
	int32 LockNum = 0;

};
