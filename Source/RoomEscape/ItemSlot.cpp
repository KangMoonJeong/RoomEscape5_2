#include "ItemSlot.h"
#include "Components\Button.h"
#include "Components\Image.h"
#include "Engine\Texture2D.h"
#include "Blueprint\WidgetBlueprintLibrary.h"
#include "DraggedItem.h"
#include "ItemDrag.h"
#include "RE_PlayerController.h"
#include "Kismet/GamePlayStatics.h"
#include "RE_GameInstance.h"
#include "FP_FirstPerson\FP_FirstPersonCharacter.h"

bool UItemSlot::Initialize()
{
	if (!Super::Initialize())
		return false;
	
	return true;
}






/* Native On */
FReply UItemSlot::NativeOnPreviewMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("UItemSlot::NativeOnPreviewMouseButtonDownB"));

	AFP_FirstPersonCharacter* PlayerCharacter = Cast<AFP_FirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerCharacter->SetIntemInspectionPath(ItemNum);




	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, FKey("LeftMouseButton"));
	

	return Reply.NativeReply;
}

void UItemSlot::NativeOnDragDetected(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent, UDragDropOperation *& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (!IsValid(ItemImage))
		return;

	UDraggedItem* DI = CreateWidget<UDraggedItem>(this, DraggedClass);
	DI->SetOwningPlayer(GetOwningPlayer());
	DI->SetSlotImage(ItemImage);


	UItemDrag* ItemDrag = Cast<UItemDrag>(UWidgetBlueprintLibrary::CreateDragDropOperation(ItemDragClass));

	if (!(ItemDrag && DI))
		return;
	
	
	ItemDrag->SetItemSlotProperties(ItemImage, ItemNum, ItemSlotIndex, this);
	ItemDrag->DefaultDragVisual = DI;
	ItemDrag->Pivot = EDragPivot::MouseDown;
	OutOperation = ItemDrag;
}

bool UItemSlot::NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{
	UItemDrag* ItemDrag = Cast<UItemDrag>(InOperation);
	if (!ItemDrag ) 
		return false;

	
	UTexture2D* ToSlotTexture = ItemImage;
	int32 ToItemNum = ItemNum;

	SwapItemSlotProperties(ItemDrag->DraggedItemTexture, ItemDrag->ItemNum);
	ItemDrag->FromItemSlot->SwapItemSlotProperties(ToSlotTexture, ToItemNum);
	
	return true;
}





/* Item Properties*/
void UItemSlot::SetItemSlotProperties(UTexture2D * SetTexture, int32 SetItemSlotIndex, int32 SetItemNum)
{
	SlotImage->SetBrushFromTexture(SetTexture);
	ItemImage = SetTexture;
	ItemSlotIndex = SetItemSlotIndex;
	ItemNum = SetItemNum;

}

void UItemSlot::SwapItemSlotProperties(UTexture2D * SetTexture, int32 SetItemNum)
{
	SlotImage->SetBrushFromTexture(SetTexture);
	ItemImage = SetTexture;
	ItemNum = SetItemNum;
}





/* Get Data */
int32 UItemSlot::GetItemNum()
{
	return ItemNum;
}






/* Press Item Slot */
void UItemSlot::PressedImageToVisible()
{
	Pressed_Image->SetVisibility(ESlateVisibility::Visible);
}

void UItemSlot::PressedImageToHidden()
{
	Pressed_Image->SetVisibility(ESlateVisibility::Hidden);

}

