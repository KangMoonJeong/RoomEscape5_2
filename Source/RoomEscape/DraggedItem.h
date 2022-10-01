// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DraggedItem.generated.h"

/**
 * 
 */
UCLASS()
class ROOMESCAPE_API UDraggedItem : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual bool Initialize();


	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UImage* SlotImage;


public:
	void SetSlotImage(class UTexture2D* Set);
	
};
