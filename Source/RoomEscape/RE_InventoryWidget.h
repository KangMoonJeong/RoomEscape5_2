#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_InventoryWidget.generated.h"

UCLASS()
class ROOMESCAPE_API URE_InventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize();

protected:
	UPROPERTY(meta = (BindWidget))
	class UGridPanel* ItemSlot_GridPanel;

	UPROPERTY(meta = (BindWidget))
	class URE_ItemSlotBarWidget* ItemSlotBarWidget4;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> ItemSlotClass;





	/* When Load Game, Open InventoryWidget from WholeWidget*/
public:
	void InitializeData();
	void InitializeItemSlot_GridPanel();
	void InitializeItemSlotBarWidget();
};
