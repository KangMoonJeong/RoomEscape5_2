// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggedItem.h"
#include "Components/Image.h"
#include "Engine\Texture2D.h"
#include "Blueprint\WidgetBlueprintLibrary.h"

bool UDraggedItem::Initialize()
{
	if (!Super::Initialize())
		return false;

	return true;
}

void UDraggedItem::SetSlotImage(UTexture2D * Set)
{
	SlotImage->SetBrushFromTexture(Set);
}
