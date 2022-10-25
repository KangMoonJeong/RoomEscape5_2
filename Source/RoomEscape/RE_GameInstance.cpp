#include "RE_GameInstance.h"
#include "RE_PlayerController.h"
#include "Engine\Texture2D.h"
#include "RE_Dialogue.h"
#include "ItemSlot.h"
#include "RE_DialogueWidget.h"



void URE_GameInstance::Init()
{
	Super::Init();
}

/* Initialize CurrentChapterIndex, CurrentQuestIndex, CurrentQuest */
void URE_GameInstance::InitializeQuestProperties(TArray<FChapter> SetChapter, int32 SetLoveCount, int32 SetChapterIdex, int32 SetQuestIndex)
{
	if (SetChapter.Num() == 0) 
	{
		Chapter = InitChapter;
		CurrentChapterIndex = SetChapterIdex;
		CurrentQuestIndex = SetQuestIndex;
		CurrentQuest = Chapter[0].Quest[0];
		LoveCount = 10;
		bLastIndex = false;
		return;
	}
	else
	{
		CurrentChapterIndex = SetChapterIdex;
		CurrentQuestIndex = SetQuestIndex;
		Chapter = SetChapter;
		CurrentQuest = Chapter[SetChapterIdex].Quest[SetQuestIndex];
		SetQuestActorNumMapFromInventory();
		LoveCount = SetLoveCount;
	}
}





void URE_GameInstance::SetQuestActorNumMapFromInventory()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;

	TMap<int32, bool> InventoryItem = NoLimitItemSlotMap;
	for (auto& Elem : InventoryItem)
	{
		if (Elem.Value == true)
			IsQuestMapContainsItemNum(Elem.Key);
	}

}

bool URE_GameInstance::IsCompleteQuest()
{
	for (auto& Elem : CurrentQuest.QuestActorNumMap)
	{
		if (Elem.Value == false)
			return false;
	}

	for (auto& Elem : CurrentQuest.LockActorNumMap)
	{
		if (Elem.Value == false)
			return false;
	}

	return true;
}

void URE_GameInstance::SetCurrentQuestElement()
{
	SetQuestActorNumMapFromInventory();

	CurrentQuest.LockActorNumMap = Chapter[CurrentChapterIndex].Quest[CurrentQuestIndex].LockActorNumMap;
}

bool URE_GameInstance::SetNextQuest(int32 AddIndex)
{
	if (CurrentChapterIndex == MaxChapterIndex && CurrentQuestIndex == MaxQuestIndex)
		return false;


	CurrentQuestIndex += AddIndex;

	if (CurrentQuestIndex >= Chapter[CurrentChapterIndex].Quest.Num())
	{
		CurrentChapterIndex++;
		CurrentQuestIndex = 0;
	}


	if (CurrentChapterIndex == MaxChapterIndex && CurrentQuestIndex == MaxQuestIndex)
	{
		UE_LOG(LogTemp, Warning, TEXT("if (CurrentChapterIndex == MaxChapterIndex && CurrentQuestIndex == MaxQuestIndex)"))
		bLastIndex = true;
	}


	CurrentQuest = Chapter[CurrentChapterIndex].Quest[CurrentQuestIndex];

	SetCurrentQuestElement();

	return true;
}

void URE_GameInstance::OpenDialogueWidget()
{
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;

	URE_DialogueWidget* DialogueWidget = CreateWidget<URE_DialogueWidget>(GetWorld(), DialogueWidgetClass);
	

	RE_PlayerController->OnCurrentWidgetOffHUD(DialogueWidget, EInputMode::EIM_UIOnly);
	DialogueWidget->InitializeProperties(CurrentQuest.DialogueFileName, LoveCount, bLastIndex);
}




/* When Get Item */
bool URE_GameInstance::IsQuestMapContainsItemNum(int32 ItemNum)
{
	if (!CurrentQuest.QuestActorNumMap.Contains(ItemNum))
	{
		return false;
	}
	else
	{
		CurrentQuest.QuestActorNumMap[ItemNum] = true;
		return true;
	}
}

void URE_GameInstance::GetItem(int32 ItemNum)
{
	if (!IsQuestMapContainsItemNum(ItemNum))
		return;

	if (!IsCompleteQuest())
		return;

	if (!SetNextQuest(1))
		return;


	OpenDialogueWidget();
}





/* When Get Unlock Item */
void URE_GameInstance::SetUnLockedActorNumToChapter(int32 ChpaterIndex, int32 QuestIndex, int32 UnLockedActor)
{
	if (Chapter[ChpaterIndex].Quest[QuestIndex].LockActorNumMap.Contains(UnLockedActor))
		Chapter[ChpaterIndex].Quest[QuestIndex].LockActorNumMap[UnLockedActor] = true;
}

void URE_GameInstance::SetUnLockedActorNumToCurrentQuest(int32 ChapterIndex, int32 QuestIndex, int32 UnLockedActor)
{
	if ((CurrentChapterIndex == ChapterIndex) && (CurrentQuestIndex == QuestIndex))
	{
		if (CurrentQuest.LockActorNumMap.Contains(UnLockedActor))
			CurrentQuest.LockActorNumMap[UnLockedActor] = true;
	}
}

void URE_GameInstance::GetUnLockedActorNum(int32 ChpaterIndex, int32 QuestIndex, int32 UnLockedActor, UUserWidget* TelegramWidget)
{
	SetUnLockedActorNumToChapter(ChpaterIndex, QuestIndex, UnLockedActor);
	SetUnLockedActorNumToCurrentQuest(ChpaterIndex, QuestIndex, UnLockedActor);

	if (!IsCompleteQuest())
		return;

	if (!SetNextQuest(1))
		return;

	if(!TelegramWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("if(!TelegramWidget)"));
		ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
		if (!RE_PlayerController)
			return;
		RE_PlayerController->OnHUDOffCurrentWidget();

	}
	OpenDialogueWidget();
}





/* Get ChapterIndex QuestIndex */
int32 URE_GameInstance::GetCurrentChpaterIndex()
{
	return CurrentChapterIndex;
}

int32 URE_GameInstance::GetCurrentQuestIndex()
{
	return CurrentQuestIndex;
}

TArray<FChapter> URE_GameInstance::GetWholeChapter()
{
	return Chapter;
}





/* ItemSlot */
void URE_GameInstance::InitializeAllItemSlotData(TArray<UItemSlot*> SetTenArray, TArray<UItemSlot*> SetOtherArray, TArray<UItemSlot*> SetNoArray, TMap<int32, bool> SetTenMap, TMap<int32, bool> SetOtherMap, TMap<int32, bool> SetNoMap, TArray<int32> SetSolvedQuestMap, TArray<int32> SetDestroyedArray)
{
	TenLimitItemSlotArray = SetTenArray;
	OtherLimitItemSlotArray = SetOtherArray;
	NoLimitItemSlotArray = SetNoArray;
	TenLimitItemSlotMap = SetTenMap;
	OtherLimitItemSlotMap = SetOtherMap;
	NoLimitItemSlotMap = SetNoMap;
	SolvedQuestMap = SetSolvedQuestMap;
	DestroyedItemNumArray = SetDestroyedArray;
}

int32 URE_GameInstance::GetTenLimitItemSlotArrayNum()
{
	return TenLimitItemSlotArray.Num();
}

int32 URE_GameInstance::GetSelectedItemSlotNum(int32 SelectedIndex)
{
	if (TenLimitItemSlotArray[SelectedIndex]->GetItemNum())
	{
		UE_LOG(LogTemp, Warning, TEXT("TenLimitItemSlotArray[SelectedIndex]->GetItemNum() : %d"), TenLimitItemSlotArray[SelectedIndex]->GetItemNum())
		return TenLimitItemSlotArray[SelectedIndex]->GetItemNum();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("!!!!!!!!!!!!!!!!TenLimitItemSlotArray[SelectedIndex]->GetItemNum() : %d"), TenLimitItemSlotArray[SelectedIndex]->GetItemNum())
		return -1;
	}
}

TArray<UItemSlot*> URE_GameInstance::GetTenLimitItemSlotArray()
{
	if (TenLimitItemSlotArray.Num() != 0)
		return TenLimitItemSlotArray;
	else
		return {};
}

TArray<UItemSlot*> URE_GameInstance::GetOtherLimitItemSlotArray()
{
	if (OtherLimitItemSlotArray.Num() != 0)
		return OtherLimitItemSlotArray;
	else
		return {};
}

TArray<UItemSlot*> URE_GameInstance::GetNoLimitItemSlotArray()
{
	return NoLimitItemSlotArray;
}

TMap<int32, bool> URE_GameInstance::GetNoLimitItemSlotMap()
{
	int32 i = 0;
	TMap<int32, bool> EmptyMap = {};

	for (auto& ArrayElem : NoLimitItemSlotArray)
	{
		EmptyMap.Add(ArrayElem->GetItemNum(), true);
		i++;
	}


	return EmptyMap;
}

TMap<int32, bool> URE_GameInstance::GetOtherLimitItemSlotMap()
{
	int32 i = 0;
	TMap<int32, bool> EmptyMap = {};

	for (auto& ArrayElem : TenLimitItemSlotArray)
	{

		EmptyMap.Add(ArrayElem->GetItemNum(), true);
		i++;
	}

	return EmptyMap;
}

TMap<int32, bool> URE_GameInstance::GetTenLimitItemSlotMap()
{
	int32 i = 0;
	TMap<int32, bool> EmptyMap = {};

	for (auto& ArrayElem : TenLimitItemSlotArray)
	{

		EmptyMap.Add(ArrayElem->GetItemNum(), true);
		i++;
	}

	return EmptyMap;
}


bool URE_GameInstance::SetTenLimitItemSlotArrayElement(int32 SetItemNum)
{
	if (TenLimitItemSlotArray.Num() == 10)
		return false;

	UItemSlot* ItemSlot = CreateWidget<UItemSlot>(this, ItemSlotClass);

	FString TexturePath = ItemSlotTexureSoftObjectPath[SetItemNum].GetAssetPathString();
	UTexture2D* Texture = LoadObject<UTexture2D>(this, *TexturePath);

	ItemSlot->SetItemSlotProperties(Texture, TenLimitItemSlotArray.Num(), SetItemNum);
	TenLimitItemSlotArray.Add(ItemSlot);

	return true;
}

void URE_GameInstance::SetOtherLimitItemSlotArrayElement(int32 SetItemNum)
{
	UItemSlot* ItemSlot = CreateWidget<UItemSlot>(this, ItemSlotClass);

	if (!ItemSlotTexureSoftObjectPath.IsValidIndex(SetItemNum))
		return;

	FString TexturePath = ItemSlotTexureSoftObjectPath[SetItemNum].GetAssetPathString();
	UTexture2D* Texture = LoadObject<UTexture2D>(this, *TexturePath);
	if (Texture)
	{
		ItemSlot->SetItemSlotProperties(Texture, NoLimitItemSlotArray.Num(), SetItemNum);
		OtherLimitItemSlotArray.Add(ItemSlot);
	}
}

void URE_GameInstance::SetNoLimitItemSlotArrayElement(int32 SetItemNum)
{
	UItemSlot* ItemSlot = CreateWidget<UItemSlot>(this, ItemSlotClass);

	if (!ItemSlotTexureSoftObjectPath.IsValidIndex(SetItemNum))
		return;

	FString TexturePath = ItemSlotTexureSoftObjectPath[SetItemNum].GetAssetPathString();
	UTexture2D* Texture = LoadObject<UTexture2D>(this, *TexturePath);
	if (Texture)
	{
		ItemSlot->SetItemSlotProperties(Texture, NoLimitItemSlotArray.Num(), SetItemNum);
		NoLimitItemSlotArray.Add(ItemSlot);
	}
}

void URE_GameInstance::SetTenLimitItemSlotDataMap(int32 ItemNum, bool InInventory)
{
	TenLimitItemSlotMap.Add(ItemNum, InInventory);
}

void URE_GameInstance::SetOtherLimitItemSlotDataMap(int32 ItemNum, bool InInventory)
{
	OtherLimitItemSlotMap.Add(ItemNum, InInventory);
}

void URE_GameInstance::SetNoLimitItemSlotDataMap(int32 ItemNum, bool InInventory)
{
	NoLimitItemSlotMap.Add(ItemNum, InInventory);
}










/* Unlock Item to Quest */
TArray<int32> URE_GameInstance::GetSolvedQuestMap()
{
	return SolvedQuestMap;
}

void URE_GameInstance::AddSolvedQuestMapElement(int32 AddNum)
{
	SolvedQuestMap.Add(AddNum);
	UE_LOG(LogTemp, Warning, TEXT("AddNum : %d"), AddNum);
}

bool URE_GameInstance::CheckContainSolvedQuestMap(int32 ItemNum)
{
	return SolvedQuestMap.Contains(ItemNum);
}




void URE_GameInstance::DeleteTenLimitArrayElementByIndex(int32 Index)
{
	if (!TenLimitItemSlotArray.IsValidIndex(Index))
		return;

	int32 ItemNum = TenLimitItemSlotArray[Index]->GetItemNum();

	if (!TenLimitItemSlotMap.Contains(ItemNum))
		return;

	TenLimitItemSlotMap.Remove(ItemNum);
	TenLimitItemSlotArray[Index]->RemoveFromParent();
	TenLimitItemSlotArray.RemoveAt(Index);
}

void URE_GameInstance::DeleteTenLimitArrayElementByItemNum(int32 ItemNum)
{
	if (!TenLimitItemSlotMap.Contains(ItemNum))
		return;

	TenLimitItemSlotMap.Remove(ItemNum);
	int32 i = 0;
	for (auto& Elem : TenLimitItemSlotArray)
	{
		if (Elem->GetItemNum() == ItemNum)
		{
			// Array
			TenLimitItemSlotArray[i]->RemoveFromParent();
			TenLimitItemSlotArray.RemoveAt(i);
			return;
		}
		i++;
	}
}

void URE_GameInstance::DeleteOtherLimitArrayElementByIndex(int32 Index)
{
	if (!OtherLimitItemSlotArray.IsValidIndex(Index))
		return;

	int32 ItemNum = OtherLimitItemSlotArray[Index]->GetItemNum();

	if (!OtherLimitItemSlotMap.Contains(ItemNum))
		return;
	
	OtherLimitItemSlotMap.Remove(ItemNum);
	OtherLimitItemSlotArray[Index]->RemoveFromParent();
	OtherLimitItemSlotArray.RemoveAt(Index);
}

void URE_GameInstance::DeleteOtherLimitArrayElementByItemNum(int32 ItemNum)
{
	if (!OtherLimitItemSlotMap.Contains(ItemNum))
		return;

	OtherLimitItemSlotMap.Remove(ItemNum);


	int32 i = 0;
	for (auto& Elem : OtherLimitItemSlotArray)
	{
		if (Elem->GetItemNum() == ItemNum)
		{
			// Array
			OtherLimitItemSlotArray[i]->RemoveFromParent();
			OtherLimitItemSlotArray.RemoveAt(i);
			return;
		}
		i++;
	}
}

void URE_GameInstance::DeleteNoLimitArrayElementByIndex(int32 Index)
{
	if (!NoLimitItemSlotArray.IsValidIndex(Index))
		return;

	int32 ItemNum = NoLimitItemSlotArray[Index]->GetItemNum();

	if (!NoLimitItemSlotMap.Contains(ItemNum))
		return;

	NoLimitItemSlotMap.Remove(ItemNum);
	if (NoLimitItemSlotArray.IsValidIndex(Index))
	{
		NoLimitItemSlotArray[Index]->RemoveFromParent();
		NoLimitItemSlotArray.RemoveAt(Index);
	}
}

void URE_GameInstance::DeleteNoLimitArrayElementByItemNum(int32 ItemNum)
{
	if (!NoLimitItemSlotMap.Contains(ItemNum))
		return;

	NoLimitItemSlotMap.Remove(ItemNum);
	
	int32 i = 0;
	for (auto& Elem : NoLimitItemSlotArray)
	{
		if (Elem->GetItemNum() == ItemNum)
		{
			// Array
			NoLimitItemSlotArray[i]->RemoveFromParent();
			NoLimitItemSlotArray.RemoveAt(i);
			return;
		}
		i++;
	}
}






TArray<int32> URE_GameInstance::GetDestroyedItemNumArray()
{
	return DestroyedItemNumArray;
}

void URE_GameInstance::SetDestroyedItemNumArray(TArray<int32> SetArray)
{
	DestroyedItemNumArray = SetArray;
}

void URE_GameInstance::AddDestroyedItemNumArray(int32 ItemNum)
{
	DestroyedItemNumArray.Add(ItemNum);
}

int32 URE_GameInstance::GetNoLimitSlotArrayFirstItemNum()
{
	if (NoLimitItemSlotArray.IsValidIndex(0))
	{
		return NoLimitItemSlotArray[0]->GetItemNum();
	}
	else
	{
		return -1;
	}
}







void URE_GameInstance::SetLoveCount(int32 SetLoveCount)
{
	LoveCount = SetLoveCount;
}

int32 URE_GameInstance::GetLoveCount()
{
	return LoveCount;
}


