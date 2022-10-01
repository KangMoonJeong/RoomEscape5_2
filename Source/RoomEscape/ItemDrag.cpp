#include "ItemDrag.h"
#include "Engine\Texture2D.h"
#include "ItemSlot.h"

void UItemDrag::SetItemSlotProperties(UTexture2D * SetTexture, int32 SetItemNum, int32 SetSlotIndex, UItemSlot* SetItemSlot)
{
	FromItemSlot = CreateWidget<UItemSlot>(GetWorld(), ItemSlotClass);
	FromItemSlot = SetItemSlot;


	DraggedItemTexture = SetTexture;
	ItemNum = SetItemNum;
	SlotIndex = SetSlotIndex;
}
