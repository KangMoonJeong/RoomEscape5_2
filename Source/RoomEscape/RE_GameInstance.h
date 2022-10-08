#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine\DataTable.h"
#include "RE_QuestStruct.h"
#include "RE_GameInstance.generated.h"


UCLASS(config=Game)
class ROOMESCAPE_API URE_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;


protected:
	UPROPERTY(EditAnywhere)
	TArray<FChapter> Chapter;

	UPROPERTY(EditAnywhere)
	TArray<FChapter> InitChapter;

	UPROPERTY(EditAnywhere)
	int32 MaxChapterIndex = 0;

	UPROPERTY(EditAnywhere)
	int32 MaxQuestIndex = 0;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> ItemSlotClass;

private:
	UPROPERTY(Config)
	TArray<FSoftObjectPath> ItemSlotTexureSoftObjectPath;

	int32 CurrentChapterIndex = 0;
	int32 CurrentQuestIndex = 0;
	FQuest CurrentQuest;

	UPROPERTY()
	TArray<class UItemSlot*> TenLimitItemSlotArray;
	UPROPERTY()
	TArray<class UItemSlot*> OtherLimitItemSlotArray;
	UPROPERTY()
	TArray<class UItemSlot*> NoLimitItemSlotArray;
	UPROPERTY()
	TArray<int32> SolvedQuestMap;
	UPROPERTY()
	TMap<int32, bool> TenLimitItemSlotMap;
	UPROPERTY()
	TMap<int32, bool> OtherLimitItemSlotMap;
	UPROPERTY()
	TMap<int32, bool> NoLimitItemSlotMap;





	/* Initialize SetChapter, CurrentQuest, CurrentChapterIndex, CurrentQuestIndex */
public:
	void InitializeQuestProperties(TArray<FChapter> SetChapter, int32 SetLoveCount, int32 SetChapterIdex = 0, int32 SetQuestIndex = 0);





	/* When Get Item */
private:
	void SetQuestActorNumMapFromInventory();
	bool IsQuestMapContainsItemNum(int32 ItemNum);
	bool IsCompleteQuest();
	bool SetNextQuest(int32 AddIndex = 0);
	void OpenDialogueWidget();
	void SetCurrentQuestElement();

public:
	void GetItem(int32 ItemNum);






	/* When Get Unlock Item */
private:
	void SetUnLockedActorNumToChapter(int32 ChpaterIndex, int32 QuestIndex, int32 UnLockedActor);
	void SetUnLockedActorNumToCurrentQuest(int32 ChapterIndex, int32 QuestIndex, int32 UnLockedActor);
public:
	void GetUnLockedActorNum(int32 ChpaterIndex, int32 QuestIndex, int32 UnLockedActor);





	/* Get Data */
	int32 GetCurrentChpaterIndex();
	int32 GetCurrentQuestIndex();
	TArray<FChapter> GetWholeChapter();




	/* ItemSlot */
public:
	void InitializeAllItemSlotData(TArray<UItemSlot*> SetTenArray, TArray<UItemSlot*> SetOtherArray, TArray<UItemSlot*> SetNoArray, TMap<int32, bool> SetTenMap, TMap<int32, bool> SetOtherMap, TMap<int32, bool> SetNoMap, TArray<int32> SetSolvedQuestMap, TArray<int32> SetDestroyedArray);

	int32 GetTenLimitItemSlotArrayNum();
	int32 GetSelectedItemSlotNum(int32 SelectedIndex);


	TArray<UItemSlot*> GetTenLimitItemSlotArray();
	TArray<UItemSlot*> GetOtherLimitItemSlotArray();
	TArray<UItemSlot*> GetNoLimitItemSlotArray();
	TMap<int32, bool> GetNoLimitItemSlotMap();
	TMap<int32, bool> GetOtherLimitItemSlotMap();
	TMap<int32, bool> GetTenLimitItemSlotMap();

	bool SetTenLimitItemSlotArrayElement(int32 SetItemNum);
	void SetOtherLimitItemSlotArrayElement(int32 SetItemNum);
	void SetNoLimitItemSlotArrayElement(int32 SetItemNum);
	void SetTenLimitItemSlotDataMap(int32 ItemNum, bool InInventory);
	void SetOtherLimitItemSlotDataMap(int32 ItemNum, bool InInventory);
	void SetNoLimitItemSlotDataMap(int32 ItemNum, bool InInventory);




	/*  Item to Quest */
public:
	TArray<int32> GetSolvedQuestMap();
	void AddSolvedQuestMapElement(int32 AddNum);





	/***/
public:
	void DeleteTenLimitArrayElementByIndex(int32 Index);
	void DeleteTenLimitArrayElementByItemNum(int32 ItemNum);

	void DeleteOtherLimitArrayElementByIndex(int32 Index);
	void DeleteOtherLimitArrayElementByItemNum(int32 ItemNum);

	void DeleteNoLimitArrayElementByIndex(int32 Index);
	void DeleteNoLimitArrayElementByItemNum(int32 ItemNum);





	TArray<int32> DestroyedItemNumArray;
	TArray<int32> GetDestroyedItemNumArray();
	void SetDestroyedItemNumArray(TArray<int32> SetArray);
	void AddDestroyedItemNumArray(int32 ItemNum);




	int32 GetNoLimitSlotArrayFirstItemNum();


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> DialogueWidgetClass;

	


private:
	int32 LoveCount = 10;

public:
	void SetLoveCount(int32 SetLoveCount);
	int32 GetLoveCount();
};