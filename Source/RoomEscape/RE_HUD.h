#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_HUD.generated.h"


UCLASS()
class ROOMESCAPE_API URE_HUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class URE_ItemSlotBarWidget* ItemSlotBarWidget;

	class UImage* Crosshair_Image;

	class UTextBlock* InteractDescription_Text;





	/* Get Data */
public:
	URE_ItemSlotBarWidget* GetItemSlotBarWidget();


	/**/
public:
	void SetCrosshair_Image(bool Find);
	void SetInteractDescription_Text(UTextBlock* SetTextBlock);
};
