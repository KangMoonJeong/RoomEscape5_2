#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AddCombine.generated.h"

UCLASS()
class ROOMESCAPE_API UAddCombine : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize();


protected:
	 
	UPROPERTY(meta = (BindWidget))
	class UButton* Insepect_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* Combine_Button;

protected:


	UFUNCTION()
	void OnClicked_Insepect_Button();

	UFUNCTION()
	void OnClicked_Combine_Button();


private:
	int32 ItemNum;

public:
	void SetItemNum(int32 Set);

};
