#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveListWidget.generated.h"

UCLASS()
class ROOMESCAPE_API USaveListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize();

	
	/* Widget Switcher Setting */
protected:
	UPROPERTY(meta = (BindWidget))
	class URE_SaveListUnitWidget* SaveListUnitWidget_1;

	UPROPERTY(meta = (BindWidget))
	class URE_SaveListUnitWidget* SaveListUnitWidget_2;

	UPROPERTY(meta = (BindWidget))
	class URE_SaveListUnitWidget* SaveListUnitWidget_3;

	UPROPERTY(meta = (BindWidget))
	class URE_SaveListUnitWidget* SaveListUnitWidget_4;

	UPROPERTY(meta = (BindWidget))
	class URE_SaveListUnitWidget* SaveListUnitWidget_5;

	UPROPERTY(meta = (BindWidget))
	class URE_SaveListUnitWidget* SaveListUnitWidget_6;


public:
	void SetSaveListUnitWidgetIndex(int32 Set);




	/* X_Button On Clicked Remove From Parent */
protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* X_Button;

	
protected:
	UFUNCTION()
	void X_ButtonOnClicked();
};
