// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_ItemBar.generated.h"

/**
 * 
 */
UCLASS()
class ROOMESCAPE_API URE_ItemBar : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual bool Initialize();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> ItemSlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> AddCombineClass;



	// Widget
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UScrollBox* ItemSlot_ScrollBox;

	TArray<class UItemSlot*> TenLimitItemSlotArray;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UVerticalBox* ItemSlot_VerticalBox;

	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* MoveWidget;



	/* Item Slot */
public:
	int32 GetItemSlotIndex(UItemSlot* FindItemSlot);


	void DebugItemSlotArray();
	void CreateItemSlot(UTexture2D* SetTexture, int32 SetItemNum);
//	void SwapItemSlotSlot(int32 ToSlotIndex, int32 FromSlotIndex);


	/* Animation */
public:
	void ShowWidget();
	void HiddenWidget();






	/***/
private:
	int32 CurrentItemSlotNumToBorder = 0;
};
