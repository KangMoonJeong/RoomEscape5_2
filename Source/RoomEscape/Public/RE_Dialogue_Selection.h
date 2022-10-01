#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RE_Dialogue_Selection.generated.h"

UCLASS()
class ROOMESCAPE_API URE_Dialogue_Selection : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
	class UButton* SelectionButton1;

	UPROPERTY(meta = (BindWidget))
	class UButton* SelectionButton2;


};
