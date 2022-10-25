#include "RE_PhonePassword.h"
#include "Components\EditableText.h"
#include "Components/Button.h"
#include "Kismet\KismetTextLibrary.h"
#include "Components/Image.h"
#include "Engine\Texture2D.h"
#include "Components\WidgetSwitcher.h"


bool URE_PhonePassword::Initialize()
{
	bool Success = UUserWidget::Initialize();
	if (!Success)
		return false;

	UnLockedImage->SetBrushFromTexture(TextureArray);
	OK_Button->OnClicked.AddDynamic(this, &URE_PhonePassword::OK_Button_OnClicked);
	Previousbutton->OnClicked.AddDynamic(this, &URE_PhonePassword::Previousbutton_ButtonOnClicked);
	Removebutton->OnClicked.AddDynamic(this, &URE_PhonePassword::Removebutton_ButtonOnClicked);


	return true;
}

void URE_PhonePassword::OK_Button_OnClicked()
{
	
	if (UKismetTextLibrary::EqualEqual_TextText(Password_EditableText->GetText(), Password))
	{
		UE_LOG(LogTemp, Warning, TEXT("OK_Button_OnClicked() Yes"));
		Password_WidgetSwitcher->SetActiveWidgetIndex(1);
		UnLockedImage->SetBrushFromTexture(TextureArray);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OK_Button_OnClicked() No"));
	}
}


void URE_PhonePassword::Previousbutton_ButtonOnClicked()
{
	Password_WidgetSwitcher->SetActiveWidgetIndex(0);
}


void URE_PhonePassword::Removebutton_ButtonOnClicked()
{
	RemoveFromParent();
}
