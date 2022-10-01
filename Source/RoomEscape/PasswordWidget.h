#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PasswordWidget.generated.h"

UCLASS()
class ROOMESCAPE_API UPasswordWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize();

public:
	void VisibleWidgetSettig();

	void HidenWidgetSettig();

protected:
	UPROPERTY(EditAnywhere)
		int32 Password;

	int32 CurrentNum = 0000;

private:
	void CorrectPassword();

};
