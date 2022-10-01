#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_DialogueWidget.generated.h"

UCLASS()
class ROOMESCAPE_API URE_DialogueWidget : public UUserWidget
{
	GENERATED_BODY()



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
	int32 CurrentRowNum = 0;

public:
	void InitializeProperties(FString FileName);
	




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
};
