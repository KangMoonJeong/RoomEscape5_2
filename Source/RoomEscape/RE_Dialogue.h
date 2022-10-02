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


	UPROPERTY()
	int32 SelectBool;

	UPROPERTY()
	FText SelectDialogue1;

	UPROPERTY()
	FText SelectDialogue2;

	UPROPERTY()
	int32 Sum;

	UPROPERTY()
	int32 ResultSum1;

	UPROPERTY()
	int32 ResultSum2;


	UPROPERTY()
	int32 ResultLoveCount1;

	UPROPERTY()
	int32 ResultLoveCount2;

};
