#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_SaveListUnitWidget.generated.h"

UCLASS()
class ROOMESCAPE_API URE_SaveListUnitWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual bool Initialize();

protected:
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* SaveLoadWidgetSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* SaveLoad_SaveButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* SaveLoad_LoadButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* Load_LoadButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* SavedImage;
	
	UPROPERTY(meta = (BindWidget))
	class UImage* OpacityImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SaveStatusText;


	



	/* Save and Load */
private:
	class URE_SaveGame* GetMasterSlot();
	void SaveSelectedSlotIndex(int32 SetSlotIndex);

protected:
	UFUNCTION()
	void SaveToSlot();

	UFUNCTION()
	void LoadToSlot();

protected:
	UPROPERTY(EditAnywhere, Category = "707")
	int32 SlotIndex;

	UPROPERTY(EditAnywhere, Category = "707")
	FName MapName;

	UPROPERTY(EditAnywhere, Category = "707")
	TArray<class UTexture2D*> SavedImageArray;

private:
	void SetSaveStatus();





	/* Mouse Enter and Leave */
protected:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);





	/* Widget Switcher */
public:
	void SetActiveWidgetIndex(int Set);


	int32 Quest;
	int32 Chapter;


	/***/
	bool LoadChapterStatusFromSlot();
};
