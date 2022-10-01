#include "RE_HaveItemStorage.h"
#include "ItemSlot.h"

ARE_HaveItemStorage::ARE_HaveItemStorage()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ARE_HaveItemStorage::BeginPlay()
{
	Super::BeginPlay();
}

int32 ARE_HaveItemStorage::GetTenLimitItemSlotArrayNum()
{
	return TenLimitItemSlotArray.Num();
}

void ARE_HaveItemStorage::SetTenLimitItemSlotArrayElement(UTexture2D * SetTexture, int32 SetItemNum)
{
	//UItemSlot* ItemSlot = CreateWidget<UItemSlot>(this, ItemSlotClass);
	//ItemSlot->SetItemSlotProperties(SetTexture, TenLimitItemSlotArray.Num(), SetItemNum);
	//TenLimitItemSlotArray.Add(ItemSlot);
}



