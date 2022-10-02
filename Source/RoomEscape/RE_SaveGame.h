#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RE_QuestStruct.h"
#include "RE_SaveGame.generated.h"



UCLASS()
class ROOMESCAPE_API URE_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	URE_SaveGame();
	
	/* Get Slot Index */
	TArray<FString> SlotArray;

	UPROPERTY()
	int32 SelectedSlotIndex;

	UPROPERTY()
	TArray<int32> SavedSlotImageIndex;


	/* Get Data */
	UPROPERTY()
	TArray<FChapter> Chapter;

	UPROPERTY()
	int32 CurrentChpaterIndex;

	UPROPERTY()
	int32 CurrentQuestIndex;

	UPROPERTY()
	FVector PlayerLocation = FVector(10.f, 2170.f, 94.490028f);

	UPROPERTY()
	TArray<int32> DestroyedItemNumArray;

	UPROPERTY()
	TMap<int32, bool> TenLimitItemSlotMap;

	UPROPERTY()
	TMap<int32, bool> OtherLimitItemSlotMap;

	UPROPERTY()
	TMap<int32, bool> NoLimitItemSlotMap;

	UPROPERTY()
	TArray<int32> SolvedQuestMap; 
	

	UPROPERTY()
	int32 LoveCount;


};
