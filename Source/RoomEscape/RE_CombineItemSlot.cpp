#include "RE_CombineItemSlot.h"
#include "ItemDrag.h"
#include "Engine\Texture2D.h"
#include "Components\Image.h"
#include "RE_CombineWidget.h"


bool URE_CombineItemSlot::Initialize()
{
	if (!Super::Initialize())
		return false;

	return true;
}






bool URE_CombineItemSlot::NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{
	UItemDrag* ItemDrag = Cast<UItemDrag>(InOperation);
	if (!ItemDrag)
		return false;
	

	SlotImage->SetBrushFromTexture(ItemDrag->DraggedItemTexture);
	ItemNum = ItemDrag->ItemNum;

	CombineWidget->InspectionAddStatus();

	return true;
}






void URE_CombineItemSlot::SetParentWidget(class URE_CombineWidget* SetCombineWidget)
{
	CombineWidget = SetCombineWidget;
}

int32 URE_CombineItemSlot::GetItemNum()
{
	return ItemNum;
}

void URE_CombineItemSlot::CleanItemSlot()
{
	SlotImage->SetBrushFromTexture(DefaultSlotImage);
	ItemNum = 0;

}


