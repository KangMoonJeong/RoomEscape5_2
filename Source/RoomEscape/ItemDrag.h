// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDrag.generated.h"

/**
 * 
 */
UCLASS()
class ROOMESCAPE_API UItemDrag : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UTexture2D* DraggedItemTexture;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> ItemSlotClass;

	int32 ItemNum;
	int32 SlotIndex;
	class UItemSlot* FromItemSlot;

	void SetItemSlotProperties(UTexture2D* SetTexture, int32 SetItemNum, int32 SetSlotIndex, UItemSlot* SetItemSlot);
	
};
