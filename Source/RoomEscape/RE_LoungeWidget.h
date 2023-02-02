#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_LoungeWidget.generated.h"

UCLASS()
class ROOMESCAPE_API URE_LoungeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize();
	

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* New_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* Storage_Button;

	/*UPROPERTY(meta = (BindWidget))
	class UButton* Sound_Button;*/

	UPROPERTY(meta = (BindWidget))
	class UButton* Exit_Button;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* DetailContent_Switcher;

	UPROPERTY(meta = (BindWidget))
	class UButton* NewYes_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* NewNo_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitYes_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitNo_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* StorageNo_Button;

	UFUNCTION()
	void New_ButtonOnClicked();

	UFUNCTION()
	void Storage_ButtonOnClicked();

	/*UFUNCTION()
	void Sound_ButtonOnClicked();*/

	UFUNCTION()
	void Exit_ButtonOnClicked();

	UFUNCTION()
	void NewYes_ButtonOnClicked();

	UFUNCTION()
	void NewNo_ButtonOnClicked();

	UFUNCTION()
	void ExitYes_ButtonOnClicked();

	UFUNCTION()
	void ExitNo_ButtonOnClicked();

	UFUNCTION()
	void StorageNo_ButtonOnClicked();


	UPROPERTY(EditAnywhere, Category = "707")
	FName MapName;




	UPROPERTY(EditAnywhere, Category = "707")
	int32 SettingWidgetIndex;

	UPROPERTY(EditAnywhere, Category = "707")
	int32 NewWidgetIndex;

	UPROPERTY(EditAnywhere, Category = "707")
	int32 StorageWidgetIndex;

	UPROPERTY(EditAnywhere, Category = "707")
	int32 ExitWidgetIndex;






	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UComboBoxString* Local_ComboBox;


	UFUNCTION(BlueprintCallable)
	void SetLocalString(FString SetLocalString);


	UFUNCTION(BlueprintCallable)
	void SaveLocalStringToSaveGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LocalString;

};
