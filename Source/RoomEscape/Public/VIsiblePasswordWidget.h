#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VIsiblePasswordWidget.generated.h"

UCLASS()
class ROOMESCAPE_API UVIsiblePasswordWidget : public UUserWidget
{
	GENERATED_BODY()

		virtual bool Initialize();


public:
	void VisibleWidgetSettig();


	UFUNCTION()
	void HiddenWidgetSettig();


	UPROPERTY(EditAnywhere)
		int32 Chapter;

	UPROPERTY(EditAnywhere)
		int32 Quest;

	UPROPERTY(EditAnywhere)
		int32 LockNum;


	UPROPERTY(meta = (BindWidget))
		class UButton* X_Button;


};
