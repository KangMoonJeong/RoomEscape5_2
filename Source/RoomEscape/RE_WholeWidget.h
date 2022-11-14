#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_WholeWidget.generated.h"

UCLASS()
class ROOMESCAPE_API URE_WholeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize();



protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* Lounge_Button;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Inventory_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* Inspection_Button;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Combine_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* X_Button;
	
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* Content_WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	class URE_InventoryWidget* BP_InventoryWidget;

	UPROPERTY(meta = (BindWidget))
	class URE_CombineWidget* BP_CombineWidget;

	UPROPERTY(meta = (BindWidget))
	class URE_CameraInspectionWidget* BP_CameraInspectionWidget;


	UUserWidget* CurrentWidget = nullptr;

	bool FirstItemInspectionWidgetOpen = true;
	bool FirstCombineWidgetOpen = true;

	
	/* Select Tab */
	UFUNCTION()
	void Lounge_ButtonOnClicked();

	UFUNCTION()
	void Inventory_ButtonOnClicked();

	UFUNCTION()
	void Inspection_ButtonOnClicked();

	UFUNCTION()
	void Combine_ButtonOnClicked();

	UFUNCTION()
	void X_ButtonOnClicked();



	/***/
public:
	void RelocationInspectionGridPanel();
	void SetItemInspectionPath(int32 PathNum);

};
