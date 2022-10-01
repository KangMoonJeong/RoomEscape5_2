#include "FourDigitPasswordWidget.h"
#include "RE_PlayerController.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Engine\Texture2D.h"
#include "RE_GameInstance.h"
#include "RE_PasswordLockedItem.h"

bool UFourDigitPasswordWidget::Initialize()
{
	bool Success = UUserWidget::Initialize();
	if (!Success)
		return false;

	FourthDigitUp_Button->OnClicked.AddDynamic(this, &UFourDigitPasswordWidget::FourthDigitUp);
	ThirdDigitUp_Button->OnClicked.AddDynamic(this, &UFourDigitPasswordWidget::ThirdDigitUp);
	SecondDigitUp_Button->OnClicked.AddDynamic(this, &UFourDigitPasswordWidget::SecondDigitUp);
	FirstDigitUp_Button->OnClicked.AddDynamic(this, &UFourDigitPasswordWidget::FirstDigitUp);

	FourthDigitDown_Button->OnClicked.AddDynamic(this, &UFourDigitPasswordWidget::FourthDigitDown);
	ThirdDigitDown_Button->OnClicked.AddDynamic(this, &UFourDigitPasswordWidget::ThirdDigitDown);
	SecondDigitDown_Button->OnClicked.AddDynamic(this, &UFourDigitPasswordWidget::SecondDigitDown);
	FirstDigitDown_Button->OnClicked.AddDynamic(this, &UFourDigitPasswordWidget::FirstDigitDown);

	X_Button->OnClicked.AddDynamic(this, &UFourDigitPasswordWidget::HiddenWidgetSettig);


	VisibleWidgetSettig();

	return true;
}

void UFourDigitPasswordWidget::VisibleWidgetSettig()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;

	RE_PlayerController->OnCurrentWidgetOffHUD(this, EInputMode::EIM_UIOnly);
}


void UFourDigitPasswordWidget::HiddenWidgetSettig()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;

	RE_PlayerController->OnHUDOffCurrentWidget();
}

void UFourDigitPasswordWidget::SetLockedItem(ARE_PasswordLockedItem * SetItem)
{
	if (SetItem)
		OwnerLockedItem = SetItem;
}


void UFourDigitPasswordWidget::FourthDigitUp()
{
	FourthDigit++;
	CurrentNum += 1000;
	if (FourthDigit == 10)
	{
		FourthDigit = 0;
		CurrentNum -= 10000;
	}

	FourthDigit_Image->SetBrushFromTexture(TextureArray[FourthDigit]);
	ComparePassword();
}

void UFourDigitPasswordWidget::ThirdDigitUp()
{
	ThirdDigit++;
	CurrentNum += 100;
	if (ThirdDigit == 10)
	{
		ThirdDigit = 0;
		CurrentNum -= 1000;
	}

	ThirdDigit_Image->SetBrushFromTexture(TextureArray[ThirdDigit]);
	ComparePassword();
}

void UFourDigitPasswordWidget::SecondDigitUp()
{
	SecondDigit++;
	CurrentNum += 10;
	if (SecondDigit == 10)
	{
		SecondDigit = 0;
		CurrentNum -= 100;
	}

	SecondDigit_Image->SetBrushFromTexture(TextureArray[SecondDigit]);
	ComparePassword();
}

void UFourDigitPasswordWidget::FirstDigitUp()
{
	FirstDigit++;
	CurrentNum += 1;
	if (FirstDigit == 10)
	{
		FirstDigit = 0;
		CurrentNum -= 10;
	}

	FirstDigit_Image->SetBrushFromTexture(TextureArray[FirstDigit]);
	ComparePassword();
}

void UFourDigitPasswordWidget::FourthDigitDown()
{
	FourthDigit--;
	CurrentNum -= 1000;
	if (FourthDigit == -1)
	{
		FourthDigit = 9;
		CurrentNum += 10000;
	}

	FourthDigit_Image->SetBrushFromTexture(TextureArray[FourthDigit]);
	ComparePassword();
}

void UFourDigitPasswordWidget::ThirdDigitDown()
{
	ThirdDigit--;
	CurrentNum -= 100;
	if (ThirdDigit == -1)
	{
		ThirdDigit = 9;
		CurrentNum += 1000;
	}

	ThirdDigit_Image->SetBrushFromTexture(TextureArray[ThirdDigit]);
	ComparePassword();
}

void UFourDigitPasswordWidget::SecondDigitDown()
{
	SecondDigit--;
	CurrentNum -= 10;
	if (SecondDigit == -1)
	{
		SecondDigit = 9;
		CurrentNum += 100;
	}

	SecondDigit_Image->SetBrushFromTexture(TextureArray[SecondDigit]);
	ComparePassword();
}

void UFourDigitPasswordWidget::FirstDigitDown()
{
	
	FirstDigit--; 
	CurrentNum--; 
	if (FirstDigit == -1)
	{
		FirstDigit = 9; 
		CurrentNum += 10; 
	}

	FirstDigit_Image->SetBrushFromTexture(TextureArray[FirstDigit]);
	ComparePassword();
}

void UFourDigitPasswordWidget::ComparePassword()
{
	if (CurrentNum != Password)
		return;

	OwnerLockedItem->SolevedItem();
	
	HiddenWidgetSettig();

	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
		return;

	GameInstance->GetUnLockedActorNum(Chapter, Quest, LockNum);

}
