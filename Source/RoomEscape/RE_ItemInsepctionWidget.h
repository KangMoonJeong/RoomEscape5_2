#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_ItemInsepctionWidget.generated.h"

UCLASS()
class ROOMESCAPE_API URE_ItemInsepctionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize();



protected:
	UPROPERTY(meta = (BindWidget))
		class UGridPanel* ItemSlot_GridPanel;

	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* ItemSlot_UniformGridPanel;

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
};
