#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_ItemSlotBarWidget.generated.h"

UCLASS()
class ROOMESCAPE_API URE_ItemSlotBarWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual bool Initialize();


public:
	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_1;

	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_2;

	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_3;

	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_4;

	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_5;

	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_6;

	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_7;

	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_8;

	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_9;

	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_0;

private:
	int32 CurrentItemSlotNumToBorder = 0;
	int32 PressedLocation = -1;






public:
	/* Add Slot Element */
	void AddTenLimitItemSlotElement();
	/* When Load Game, Open InventoryWidget from WholeWidget*/
	void InitializeSlot();





	/* Press Item Slot */
public:
	void PressItemSlot(int32 PressLocation);
	void ReleaseItemSlot();

};
