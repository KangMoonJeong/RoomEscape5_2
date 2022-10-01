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

	UPROPERTY(meta = (BindWidget))
	class UButton* Sound_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* Exit_Button;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* DetailContent_Switcher;

	UPROPERTY(meta = (BindWidget))
	class UButton* NewYes_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitYes_Button;

	UFUNCTION()
	void New_ButtonOnClicked();

	UFUNCTION()
	void Storage_ButtonOnClicked();

	UFUNCTION()
	void Sound_ButtonOnClicked();

	UFUNCTION()
	void Exit_ButtonOnClicked();

	UFUNCTION()
	void NewYes_ButtonOnClicked();

	UFUNCTION()
	void ExitYes_ButtonOnClicked();

	UPROPERTY(EditAnywhere, Category = "707")
	FName MapName;
};
