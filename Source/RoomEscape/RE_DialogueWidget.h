#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_DialogueWidget.generated.h"

UCLASS()
class ROOMESCAPE_API URE_DialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//virtual bool Initialize(); 



protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* Character_Image;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CharacterName_Text;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Dialogue_Text;

	UPROPERTY(EditAnywhere)
	TArray<class UTexture2D*> CharacterImageArray;

protected:
	void SetCurrentlyRow();
	void RemoveWidget();
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

private:
	class ARE_Chapter* RE_Chapter;
	class UDataTable* TestDataTable;
	int32 CurrentRowNum = 1;

public:
	void InitializeProperties(FString FileName, int32 SetLoveCount = 10, bool SetLastIndex = false);
	




	//
protected:
	UPROPERTY(meta = (BindWidget))
	class URE_Dialogue_Selection* BP_Dialogue_Selection;


	void InspectDialogueSelectBool();
	void InspectNextDialogue();

	bool VisibleDialogueSelection = false;

	struct FRE_Dialogue* DialogueRow;

	bool HasNextDialogue = true;


	void SetSelectionDialogueCurrentlyRow();




	UFUNCTION()
	void SelectionButton1_OnClicked();

	UFUNCTION()
	void SelectionButton2_OnClicked();


	void FindCurrentRowNum();


public:
	int32 GetLoveCount();
	void InitializeData(int32 SetResultLoveCount);
	int32 LoveCount;




	///
	bool bLastIndex = false;
	void SetLastIndexLow();

	UPROPERTY(EditAnywhere)
	int32 GoodEnding1LoveCount;

	UPROPERTY(EditAnywhere)
	int32 GoodEnding1Low;

	UPROPERTY(EditAnywhere)
	int32 BadEnding1LoveCount;

	UPROPERTY(EditAnywhere)
		int32 BadEnding1Low;

	UPROPERTY(EditAnywhere)
	int32 BadEnding2LoveCount;

	UPROPERTY(EditAnywhere)
	int32 BadEnding2Low;


	UPROPERTY(EditAnywhere)
	FName MapName;



	
	//class USoundWave* MakingSound;
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SpecialEffects();


	void PlayShockAnimation();

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Shock;

};
