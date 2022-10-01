#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_CombineItemSlot.generated.h"

UCLASS()
class ROOMESCAPE_API URE_CombineItemSlot : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual bool Initialize();


protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* SlotImage;

	UPROPERTY()
	class URE_CombineWidget* CombineWidget;

	UPROPERTY(EditAnywhere)
	class UTexture2D* DefaultSlotImage;

	int32 ItemNum = -1;

protected:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);


	
public:
	void SetParentWidget(class URE_CombineWidget* SetCombineWidget);
	
	int32 GetItemNum();

	void CleanItemSlot();
};
