#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_Dialogue_Selection.generated.h"

UCLASS()
class ROOMESCAPE_API URE_Dialogue_Selection : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	class UButton* SelectionButton1;

	UPROPERTY(meta = (BindWidget))
	class UButton* SelectionButton2;


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SelectionText1;


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SelectionText2;


	virtual bool Initialize();


	/*UFUNCTION()
	void SelectionButton1_OnClicked();

	UFUNCTION()
	void SelectionButton2_OnClicked();*/
};
