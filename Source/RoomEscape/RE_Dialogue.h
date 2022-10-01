#pragma once

#include "Engine/DataTable.h"
#include "RE_Dialogue.generated.h"

USTRUCT(BlueprintType)
struct ROOMESCAPE_API FRE_Dialogue : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	int32 CharacterImage;

	UPROPERTY()
	FText CharacterName;

	UPROPERTY()
	FText Dialogue;
};
