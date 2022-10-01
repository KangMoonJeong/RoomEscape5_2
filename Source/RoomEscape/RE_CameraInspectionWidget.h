#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_CameraInspectionWidget.generated.h"

UCLASS()
class ROOMESCAPE_API URE_CameraInspectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;


protected:
	UPROPERTY(meta = (BindWidget))
	class UGridPanel* ItemSlot_GridPanel;

	UPROPERTY(meta = (BindWidget))
	class UButton* Left_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* Right_Button;

	class IItemSlotInteraction_Interface* ItemInspection_Interface;

	int32 ItemNum = 0;





	/* Setting */
public:
	void InitialSetting();
	void InitialInputSetting();
	void InitializeItemSlot_GridPanel();
	void SetChildActorClass();


	/* Click Event */
protected:
	UFUNCTION()
	void Left_ButtonOnClicked();

	UFUNCTION()
	void Right_ButtonOnClicked();




	/***/
public:
	void ReLocationItemSlot_GridPanel();
	void SetSpawnActorFromPath(int32 PathNum);
	TArray<class UItemSlot*> UpdateItemSlotArray();
};
