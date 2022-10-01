#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingWidget.generated.h"


UCLASS()
class ROOMESCAPE_API USettingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize();


protected:
	/* New Button */
	UPROPERTY(meta = (BindWidget))
	class UButton* New_Button;

	UFUNCTION()
	void New_ButtonOnClicked();






	/* SaveLoad Button */
	UPROPERTY(meta = (BindWidget))
	class UButton* SaveLoad_Button;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> SaveListWidgetClass;

	UPROPERTY()
	class USaveListWidget* SaveListWidget;

	UFUNCTION()
	void SaveLoad_ButtonOnClicked();





	/* X Button */
	UPROPERTY(meta = (BindWidget))
	class UButton* X_Button;

	UFUNCTION()
	void X_ButtonOnClicked();

	UPROPERTY(EditAnywhere, Category = "707")
	FName MapName;
};
