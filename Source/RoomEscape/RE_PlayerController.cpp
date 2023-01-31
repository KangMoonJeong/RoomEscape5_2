#include "RE_PlayerController.h"
#include "RE_HUD.h"
#include "StartWidget.h"
#include "RE_DialogueWidget.h"
#include "RE_ItemSlotBarWidget.h"
#include "RE_SaveGame.h"
#include "Kismet\GameplayStatics.h"
#include "FP_FirstPerson/FP_FirstPersonCharacter.h"
#include "RE_GameInstance.h"
#include "GameItemToSlot_Interface.h"
#include "LockedItem_Interface.h"



void ARE_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitializeLevelData();
}





/* Initialize Level */
void ARE_PlayerController::InitializeLevelData()
{
	FString LevelName = GetWorld()->GetMapName();
	LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);


	if (LevelName == StartMapName)
	{
		OpenStartMapWidget();
	}
	else if (LevelName == HouseMapName)
	{
		OpenAlchemistsHouseWidget();
		LoadSelectedSaveGameSlot();
		InitializeGameData();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Map Name : %s"), *GetWorld()->GetMapName());
	}
}





/* Access HUD->Item Slot Bar */
void ARE_PlayerController::AddSlotToHUDItemBarWidget()
{
	HUD->GetItemSlotBarWidget()->AddTenLimitItemSlotElement();
}

void ARE_PlayerController::GetHUDInitializeSlotBar()
{
	HUD->GetItemSlotBarWidget()->InitializeSlot();
}





/* Press Item Slot */
void ARE_PlayerController::DeliverSlotLocation(int32 PressLocation)
{
	HUD->GetItemSlotBarWidget()->PressItemSlot(PressLocation);
}

void ARE_PlayerController::ReleaseSlotLocation()
{
	HUD->GetItemSlotBarWidget()->ReleaseItemSlot();
}






/* Toggle Game Widget */
void ARE_PlayerController::SetInputmodeandCursor(EInputMode EStatus)
{
	switch (EStatus)
	{
	case EInputMode::EIM_GameOnly:
	{
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		bShowMouseCursor = false;
		break;
	}
	case EInputMode::EIM_UIOnly:
	{
		FInputModeUIOnly InputMode;
		SetInputMode(InputMode);
		bShowMouseCursor = true;
		break;

	}
	case EInputMode::EIM_GameandUI:
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);
		bShowMouseCursor = true;
		break;
	}
	default:
		UE_LOG(LogTemp, Warning, TEXT("ARE_PlayerController::SetInputmodeandCursor"));
		break;
	}
}

void ARE_PlayerController::OpenStartMapWidget()
{
	if (StartWidgetClass)
	{
		StartWidget = CreateWidget<UStartWidget>(this, StartWidgetClass);
		StartWidget->AddToViewport();
		SetInputmodeandCursor(EInputMode::EIM_UIOnly);
	}
}

void ARE_PlayerController::OpenAlchemistsHouseWidget()
{
	if (HUDClass)
	{
		HUD = CreateWidget<URE_HUD>(this, HUDClass);
		HUD->AddToViewport();
		SetInputmodeandCursor(EInputMode::EIM_GameOnly);

	}
	//FString Temp = "stat fps";
	//ConsoleCommand(Temp);
}

void ARE_PlayerController::OnCurrentWidgetOffHUD(UUserWidget* OnCurrentWidget, EInputMode EStatus)
{
	HUD->SetVisibility(ESlateVisibility::Hidden);
	OnCurrentWidget->AddToViewport();
	SetInputmodeandCursor(EStatus);
	CurrentWidget = OnCurrentWidget;
}

void ARE_PlayerController::OnHUDOffCurrentWidget(UUserWidget* SetCurrentWidget)
{
	if (CurrentWidget)
	{
		HUD->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
		SetInputmodeandCursor(EInputMode::EIM_GameOnly);
	}
}





/* Save Game */
void ARE_PlayerController::LoadSelectedSaveGameSlot()
{
	SaveGame = Cast<URE_SaveGame>(UGameplayStatics::CreateSaveGameObject(URE_SaveGame::StaticClass()));

	// 게임 데이터 세이브나 로드시
	if (UGameplayStatics::DoesSaveGameExist("MasterSlot", 0))
	{
		SaveGame = Cast<URE_SaveGame>(UGameplayStatics::LoadGameFromSlot("MasterSlot", 0));
		SelectedIndex = SaveGame->SelectedSlotIndex;
		
		if (UGameplayStatics::DoesSaveGameExist(SaveGame->SlotArray[SelectedIndex], 0))
			SaveGame = Cast<URE_SaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGame->SlotArray[SelectedIndex], 0));
	}

	// 게임 데이터 초기화시
	else
		SaveGame = nullptr;
}

void ARE_PlayerController::InitializeGameData()
{
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!RE_GameInstance)
		return;
	DialogueWidget = CreateWidget<URE_DialogueWidget>(GetWorld(), DialogueWidgetClass);

	// 게임 데이터 초기화시
	if (!SaveGame)
	{
		OnCurrentWidgetOffHUD(DialogueWidget, EInputMode::EIM_UIOnly);
		DialogueWidget->InitializeProperties("DataTable'/Game/707/Quest/Intro.Intro'");
		RE_GameInstance->InitializeQuestProperties({}, 0, 0);
		RE_GameInstance->InitializeAllItemSlotData({}, {}, {}, {}, {}, {}, {}, {});

		//1004
		AFP_FirstPersonCharacter* PlayerCharacter = Cast<AFP_FirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (PlayerCharacter)
			PlayerCharacter->SetActorLocation(FVector(-280.f, -160.f, -308.f));
		else
			UE_LOG(LogTemp, Warning, TEXT("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"))
			return;
	}
	


	// 게임 데이터 세이브나 로드시 -> 로드

	LoveCount = SaveGame->LoveCount;


	
	/* Game Item To Slot Data */
	TArray<int32> DestroyedItemNumArray = SaveGame->DestroyedItemNumArray;
	TMap<int32, bool> NoLimitItemSlotMap = SaveGame->NoLimitItemSlotMap;
	TMap<int32, bool> OtherLimitItemSlotMap = SaveGame->OtherLimitItemSlotMap;
	TMap<int32, bool> TenLimitItemSlotMap = SaveGame->TenLimitItemSlotMap;
	TArray<int32> SolvedQuestMap = SaveGame->SolvedQuestMap;


	RE_GameInstance->InitializeAllItemSlotData({}, {}, {}, {}, {}, {}, {}, {});
	
	TArray<AActor*> GameItemArray;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UGameItemToSlot_Interface::StaticClass(), GameItemArray);

	for (AActor* GameItemActor : GameItemArray)
	{
		IGameItemToSlot_Interface* I_GameItemToSlot = Cast<IGameItemToSlot_Interface>(GameItemActor);
	
		if (DestroyedItemNumArray.Contains(I_GameItemToSlot->GetItemNum()))
		{
			GameItemActor->Destroy();
		}
	}

	RE_GameInstance->SetDestroyedItemNumArray(DestroyedItemNumArray);


	TArray<AActor*> LockItemArray;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), ULockedItem_Interface::StaticClass(), LockItemArray);

	for (AActor* GameItemActor : LockItemArray)
	{
		ILockedItem_Interface* I_GameItemToSlot = Cast<ILockedItem_Interface>(GameItemActor);

		if (SolvedQuestMap.Contains(I_GameItemToSlot->GetItemNum()))
		{
			I_GameItemToSlot->SolevedItem();
		}
	}



	for (auto& Elem : NoLimitItemSlotMap)
	{
		RE_GameInstance->SetNoLimitItemSlotArrayElement(Elem.Key);
		RE_GameInstance->SetNoLimitItemSlotDataMap(Elem.Key, true);
	}

	for (auto& Elem : TenLimitItemSlotMap)
	{
		RE_GameInstance->SetTenLimitItemSlotArrayElement(Elem.Key);
		RE_GameInstance->SetTenLimitItemSlotDataMap(Elem.Key, true);
	}
	for (auto& Elem : OtherLimitItemSlotMap)
	{
		RE_GameInstance->SetOtherLimitItemSlotArrayElement(Elem.Key);
		RE_GameInstance->SetOtherLimitItemSlotDataMap(Elem.Key, true);
	}


	HUD->GetItemSlotBarWidget()->InitializeSlot();





	/* Player Character Location Data */
	AFP_FirstPersonCharacter* PlayerCharacter = Cast<AFP_FirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
		PlayerCharacter->SetActorLocation(SaveGame->PlayerLocation);


	/* Quest */
	RE_GameInstance->InitializeQuestProperties(SaveGame->Chapter, SaveGame->LoveCount, SaveGame->CurrentChpaterIndex, SaveGame->CurrentQuestIndex);
}

void ARE_PlayerController::SaveGameData()
{
	LoadSelectedSaveGameSlot();
	
	AFP_FirstPersonCharacter* PlayerCharacter = Cast<AFP_FirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!PlayerCharacter && !RE_GameInstance &&!DialogueWidget)
		return;
	
	SaveGame->PlayerLocation = PlayerCharacter->GetActorLocation();
	SaveGame->DestroyedItemNumArray = RE_GameInstance->GetDestroyedItemNumArray();
	SaveGame->TenLimitItemSlotMap = RE_GameInstance->GetTenLimitItemSlotMap();
	SaveGame->OtherLimitItemSlotMap = RE_GameInstance->GetOtherLimitItemSlotMap();
	SaveGame->NoLimitItemSlotMap = RE_GameInstance->GetNoLimitItemSlotMap();
	SaveGame->CurrentChpaterIndex = RE_GameInstance->GetCurrentChpaterIndex();
	SaveGame->CurrentQuestIndex = RE_GameInstance->GetCurrentQuestIndex();
	SaveGame->Chapter = RE_GameInstance->GetWholeChapter();
	SaveGame->SolvedQuestMap = RE_GameInstance->GetSolvedQuestMap();
	SaveGame->LoveCount = RE_GameInstance->GetLoveCount();

	UE_LOG(LogTemp, Warning, TEXT("ARE_PlayerController:: SaveGame->LoveCount : %d"), SaveGame->LoveCount);
	UE_LOG(LogTemp, Warning, TEXT("ARE_PlayerController:: RE_GameInstance->LoveCount : %d"), RE_GameInstance->GetLoveCount());

	

	UGameplayStatics::SaveGameToSlot(SaveGame, SaveGame->SlotArray[SelectedIndex], 0);
}

void ARE_PlayerController::DeleteGameData()
{
	SaveGame = Cast<URE_SaveGame>(UGameplayStatics::CreateSaveGameObject(URE_SaveGame::StaticClass()));
	if (UGameplayStatics::DoesSaveGameExist("MasterSlot", 0))
		SaveGame = Cast<URE_SaveGame>(UGameplayStatics::LoadGameFromSlot("MasterSlot", 0));


	for (int i = 0; i < 7; i++)
	{
		if (UGameplayStatics::DoesSaveGameExist(SaveGame->SlotArray[i], 0))
		{
			UGameplayStatics::DeleteGameInSlot(SaveGame->SlotArray[i], 0);
		}
	}
}

