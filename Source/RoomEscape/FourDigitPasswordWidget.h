#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FourDigitPasswordWidget.generated.h"

UCLASS()
class ROOMESCAPE_API UFourDigitPasswordWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize();






protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* FourthDigitUp_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* ThirdDigitUp_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* SecondDigitUp_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* FirstDigitUp_Button;


	UPROPERTY(meta = (BindWidget))
	class UButton* FourthDigitDown_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* ThirdDigitDown_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* SecondDigitDown_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* FirstDigitDown_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* X_Button;


	UPROPERTY(meta = (BindWidget))
	class UImage* FirstDigit_Image;

	UPROPERTY(meta = (BindWidget))
	class UImage* SecondDigit_Image;

	UPROPERTY(meta = (BindWidget))
	class UImage* ThirdDigit_Image;

	UPROPERTY(meta = (BindWidget))
	class UImage* FourthDigit_Image;

	UPROPERTY(EditAnywhere)
	TArray<class UTexture2D*> TextureArray;

private:
	UPROPERTY()
	int32 CurrentNum = 0000;

	UPROPERTY(EditAnywhere)
	int32 Password;

	int32 FirstDigit = 0;
	int32 SecondDigit = 0;
	int32 ThirdDigit = 0;
	int32 FourthDigit = 0;

	UPROPERTY(EditAnywhere)
	int32 Chapter;
	
	UPROPERTY(EditAnywhere)
	int32 Quest;

	UPROPERTY(EditAnywhere)
	int32 LockNum;


protected:
	UFUNCTION()
	void FourthDigitUp();

	UFUNCTION()
	void ThirdDigitUp();

	UFUNCTION()
	void SecondDigitUp();

	UFUNCTION()
	void FirstDigitUp();

	UFUNCTION()
	void FourthDigitDown();

	UFUNCTION()
	void ThirdDigitDown();

	UFUNCTION()
	void SecondDigitDown();

	UFUNCTION()
	void FirstDigitDown();


	void ComparePassword();


public:
	void VisibleWidgetSettig();

	UFUNCTION()
	void HiddenWidgetSettig();






	/***/
	class ARE_PasswordLockedItem* OwnerLockedItem;

	void SetLockedItem(class ARE_PasswordLockedItem* SetItem);
};
