#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartWidget.generated.h"

UCLASS()
class ROOMESCAPE_API UStartWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	virtual bool Initialize();
	



	/* OnClicked New Game Button */
protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* NewGame_Button;

	UFUNCTION()
	void NewGameOnClicked();

	UPROPERTY(EditAnywhere, Category = "707")
	FName MapName;





	/* OnClicked Load Game Button */
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> SaveListWidgetClass;

	UPROPERTY()
	class USaveListWidget* SaveListWidget;


	UPROPERTY(meta = (BindWidget))
	class UButton* Load_Button;

	UFUNCTION()
	void LoadOnClicked();


};
