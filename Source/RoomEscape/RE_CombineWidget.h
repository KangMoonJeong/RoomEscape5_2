#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_CombineWidget.generated.h"


USTRUCT()
struct ROOMESCAPE_API FItemCombine
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		int32 FirstItemNum;

	UPROPERTY(EditAnywhere)
		int32 SecondItemNum;

	UPROPERTY(EditAnywhere)
		int32 ResultItemNum;
};





UCLASS()
class ROOMESCAPE_API URE_CombineWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual bool Initialize();





protected:
	/*UPROPERTY(meta = (BindWidget))
	class UGridPanel* ItemSlot_GridPanel;*/

	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* ItemSlot_UniformGridPanel;

	UPROPERTY(meta = (BindWidget))
		class URE_CombineItemSlot* FirstCombineItemSlot;

	UPROPERTY(meta = (BindWidget))
		class URE_CombineItemSlot* SecondCombineItemSlot;

	UPROPERTY(EditAnywhere)
		TArray<FItemCombine> CombineListArray;

	int32 Row = 0;
	int32 Column = 0;





	/* Initial Settings */
public:
	void InitialSetting();
protected:
	void InitializeItemSlot_GridPanel();
	void InitializeCombineItemSlot();





	/* Combine and Add Item Slot */
protected:
	void AddItemSlot_GridPanel();
	void CreateItemSlot(int32 ItemNum);
	void DeleteItemSlot(int32 FirstItemNum, int32 SecondItemNum);
public:
	void InspectionAddStatus();



	/***/
	void ReLocationItemSlot_GridPanel();
	void ClearCombineItemSlot();
};
