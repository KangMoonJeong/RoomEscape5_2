#include "RE_HUD.h"
#include "RE_ItemBar.h"
#include "Components\TextBlock.h"
#include "RE_ItemSlotBarWidget.h"



void URE_HUD::SetCrosshair_Image(bool Find)
{
	//if (Find)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("true"))
	//}
	//else
	//	UE_LOG(LogTemp, Warning, TEXT("false"))
}

void URE_HUD::SetInteractDescription_Text(UTextBlock * SetTextBlock)
{

}

URE_ItemSlotBarWidget * URE_HUD::GetItemSlotBarWidget()
{
	return ItemSlotBarWidget;
}


