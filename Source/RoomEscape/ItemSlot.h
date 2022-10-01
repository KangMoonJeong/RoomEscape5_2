#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlot.generated.h"

UCLASS()
class ROOMESCAPE_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> DraggedClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDragDropOperation> ItemDragClass;

	UPROPERTY(meta = (BindWidget))
	class UButton* SlotButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* SlotImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* Pressed_Image;

	UPROPERTY(EditAnywhere)
	UTexture2D* ItemImage;
	
	int32 ItemNum = 0;

	int32 ItemSlotIndex;





	/* Native On */
protected:
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);





	/* Item Properties*/
public:
	void SetItemSlotProperties(UTexture2D * SetTexture, int32 SetItemSlotIndex, int32 SetItemNum);
	void SwapItemSlotProperties(UTexture2D * SetTexture, int32 SetItemNum);
	




	/* Get Data */
	int32 GetItemNum();





	/* Press Item Slot */
public:
	void PressedImageToVisible();
	void PressedImageToHidden();

};