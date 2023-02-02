#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RE_WidgetSaveGame.generated.h"

UCLASS()
class ROOMESCAPE_API URE_WidgetSaveGame : public USaveGame
{
	GENERATED_BODY()



public:
	URE_WidgetSaveGame();


	UPROPERTY()
	FString LocalString;
};
