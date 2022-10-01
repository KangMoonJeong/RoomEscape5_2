
#pragma once

#include "Engine\DataTable.h"
#include "RE_QuestStruct.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct  ROOMESCAPE_API FQuest
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString DialogueFileName;

	UPROPERTY(EditAnywhere)
	TMap<int32, bool> QuestActorNumMap;

	UPROPERTY(EditAnywhere)
	TMap<int32, bool> LockActorNumMap;
};


USTRUCT(BlueprintType, Blueprintable)
struct ROOMESCAPE_API FChapter
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FQuest> Quest;
};


UCLASS(BlueprintType, Blueprintable)
class ROOMESCAPE_API URE_QuestStruct : public UObject
{
	GENERATED_BODY()
};