// Fill out your copyright notice in the Description page of Project Settings.


#include "RE_Telegram.h"
#include "Components\EditableText.h"
#include "Components/Button.h"
#include "Components\WidgetSwitcher.h"
#include "Kismet\KismetTextLibrary.h"
#include "RoomEscape\RE_PlayerController.h"
#include "RoomEscape\RE_GameInstance.h"


bool URE_Telegram::Initialize()
{
	bool Success = UUserWidget::Initialize();
	if (!Success)
		return false;

	Dialogue_Button_One->OnClicked.AddDynamic(this, &URE_Telegram::Dialogue_Button_One_ButtonOnClicked);
	Dialogue_Button_Two->OnClicked.AddDynamic(this, &URE_Telegram::Dialogue_Button_Two_ButtonOnClicked);
	Dialogue_Button_Three->OnClicked.AddDynamic(this, &URE_Telegram::Dialogue_Button_Three_ButtonOnClicked);
	/*OK_Button_One->OnClicked.AddDynamic(this, &URE_Telegram::OK_Button_One_OnClicked);
	OK_Button_Two->OnClicked.AddDynamic(this, &URE_Telegram::OK_Button_Two_OnClicked);
	OK_Button_Three->OnClicked.AddDynamic(this, &URE_Telegram::OK_Button_Three_OnClicked);*/
	Previousbutton_One->OnClicked.AddDynamic(this, &URE_Telegram::Previousbutton_One_OnClicked);
	Previousbutton_Two->OnClicked.AddDynamic(this, &URE_Telegram::Previousbutton_Two_OnClicked);
	Previousbutton_Three->OnClicked.AddDynamic(this, &URE_Telegram::Previousbutton_Three_OnClicked);
	Previousbutton_Four->OnClicked.AddDynamic(this, &URE_Telegram::Previousbutton_Four_OnClicked);
	Previousbutton_Five->OnClicked.AddDynamic(this, &URE_Telegram::Previousbutton_Five_OnClicked);
	Previousbutton_Six->OnClicked.AddDynamic(this, &URE_Telegram::Previousbutton_Six_OnClicked);
	//X_Button->OnClicked.AddDynamic(this, &URE_Telegram::X_Button_OnClicked);
	Password_EditableText_One->OnTextCommitted.AddDynamic(this, &URE_Telegram::Password_EditableText_One_Commit);
	Password_EditableText_Two->OnTextCommitted.AddDynamic(this, &URE_Telegram::Password_EditableText_Two_Commit);
	Password_EditableText_Three->OnTextCommitted.AddDynamic(this, &URE_Telegram::Password_EditableText_Three_Commit);

	return true;
}


void URE_Telegram::Password_EditableText_One_Commit(const FText& InText, ETextCommit::Type InCommitType)
{
	UE_LOG(LogTemp,Warning,TEXT("URE_Telegram::DelegateCommitInputText(const FText& InText, ETextCommit::Type InCommitType)"))
	if (InCommitType != ETextCommit::OnEnter)
		return;

	if (UKismetTextLibrary::EqualEqual_TextText(Password_EditableText_One->GetText(), Password_One))
	{
		URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
		//if (GameInstance->CheckContainSolvedQuestMap(ItemNum_One))
		//{
			ContentWidgetSwitcher->SetActiveWidgetIndex(2);
		//}
		//else
		//{
			ContentWidgetSwitcher->SetActiveWidgetIndex(2);
			//GameInstance->AddSolvedQuestMapElement(ItemNum_One);
			//GameInstance->GetUnLockedActorNum(Chapter_One, Quest_One, LockNum_One);
		//}
	}
	else
	{
		Password_EditableText_One->SetText(FText::FromString(""));
		UE_LOG(LogTemp, Warning, TEXT("OK_Button_OnClicked() No"));
	}

}

void URE_Telegram::Password_EditableText_Two_Commit(const FText& InText, ETextCommit::Type InCommitType)
{
	if (InCommitType != ETextCommit::OnEnter)
		return;

	if (UKismetTextLibrary::EqualEqual_TextText(Password_EditableText_Two->GetText(), Password_Two))
	{
		URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance->CheckContainSolvedQuestMap(ItemNum_One))
		{
			ContentWidgetSwitcher->SetActiveWidgetIndex(4);
		}
		else
		{
			ContentWidgetSwitcher->SetActiveWidgetIndex(4);
		//	GameInstance->AddSolvedQuestMapElement(ItemNum_Two);
			//GameInstance->GetUnLockedActorNum(Chapter_Two, Quest_Two, LockNum_Two);
		}
	}
	else
	{
		Password_EditableText_One->SetText(FText::FromString(""));

		UE_LOG(LogTemp, Warning, TEXT("OK_Button_OnClicked() No"));
	}

}

void URE_Telegram::Password_EditableText_Three_Commit(const FText& InText, ETextCommit::Type InCommitType)
{
	if (InCommitType != ETextCommit::OnEnter)
		return;
	if (UKismetTextLibrary::EqualEqual_TextText(Password_EditableText_Three->GetText(), Password_Three))
	{
		URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance->CheckContainSolvedQuestMap(ItemNum_One))
		{
			ContentWidgetSwitcher->SetActiveWidgetIndex(6);
		}
		else
		{
			ContentWidgetSwitcher->SetActiveWidgetIndex(6);
			//GameInstance->AddSolvedQuestMapElement(ItemNum_Three);
			//GameInstance->GetUnLockedActorNum(Chapter_Three, Quest_Three, LockNum_Three);
		}
	}
	else
	{
		Password_EditableText_One->SetText(FText::FromString(""));

		UE_LOG(LogTemp, Warning, TEXT("OK_Button_OnClicked() No"));
	}

}

void URE_Telegram::Dialogue_Button_One_ButtonOnClicked()
{
	ContentWidgetSwitcher->SetActiveWidgetIndex(1);
}

void URE_Telegram::Dialogue_Button_Two_ButtonOnClicked()
{
	ContentWidgetSwitcher->SetActiveWidgetIndex(3);
}

void URE_Telegram::Dialogue_Button_Three_ButtonOnClicked()
{
	ContentWidgetSwitcher->SetActiveWidgetIndex(5);
}


//void URE_Telegram::OK_Button_One_OnClicked()
//{
//	if (UKismetTextLibrary::EqualEqual_TextText(Password_EditableText_One->GetText(), Password_One))
//	{
//		URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
//		if (GameInstance->CheckContainSolvedQuestMap(ItemNum_One))
//		{
//			ContentWidgetSwitcher->SetActiveWidgetIndex(2);
//		}
//		else
//		{
//			ContentWidgetSwitcher->SetActiveWidgetIndex(2);
//			GameInstance->AddSolvedQuestMapElement(ItemNum_One);
//			GameInstance->GetUnLockedActorNum(Chapter_One, Quest_One, LockNum_One);
//		}
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("OK_Button_OnClicked() No"));
//	}
//}
//
//void URE_Telegram::OK_Button_Two_OnClicked()
//{
//	if (UKismetTextLibrary::EqualEqual_TextText(Password_EditableText_Two->GetText(), Password_Two))
//	{
//		URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
//		if (GameInstance->CheckContainSolvedQuestMap(ItemNum_One))
//		{
//			ContentWidgetSwitcher->SetActiveWidgetIndex(4);
//		}
//		else
//		{
//			ContentWidgetSwitcher->SetActiveWidgetIndex(4);
//			GameInstance->AddSolvedQuestMapElement(ItemNum_Two);
//			GameInstance->GetUnLockedActorNum(Chapter_Two, Quest_Two, LockNum_Two);
//		}
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("OK_Button_OnClicked() No"));
//	}
//}
//
//void URE_Telegram::OK_Button_Three_OnClicked()
//{
//	if (UKismetTextLibrary::EqualEqual_TextText(Password_EditableText_Three->GetText(), Password_Three))
//	{
//		URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
//		if (GameInstance->CheckContainSolvedQuestMap(ItemNum_One))
//		{
//			ContentWidgetSwitcher->SetActiveWidgetIndex(6);
//		}
//		else
//		{
//			ContentWidgetSwitcher->SetActiveWidgetIndex(6);
//			GameInstance->AddSolvedQuestMapElement(ItemNum_Three);
//			GameInstance->GetUnLockedActorNum(Chapter_Three, Quest_Three, LockNum_Three);
//		}
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("OK_Button_OnClicked() No"));
//	}
//}

void URE_Telegram::Previousbutton_One_OnClicked()
{
	ContentWidgetSwitcher->SetActiveWidgetIndex(0);
}

void URE_Telegram::Previousbutton_Two_OnClicked()
{
	//ContentWidgetSwitcher->SetActiveWidgetIndex(1);

	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance->CheckContainSolvedQuestMap(ItemNum_One))
	{
		ContentWidgetSwitcher->SetActiveWidgetIndex(1);
	}
	else
	{
		ContentWidgetSwitcher->SetActiveWidgetIndex(1);
		GameInstance->AddSolvedQuestMapElement(ItemNum_One);
		GameInstance->GetUnLockedActorNum(Chapter_One, Quest_One, LockNum_One);
	}
}

void URE_Telegram::Previousbutton_Three_OnClicked()
{
	ContentWidgetSwitcher->SetActiveWidgetIndex(0);
}

void URE_Telegram::Previousbutton_Four_OnClicked()
{
	//ContentWidgetSwitcher->SetActiveWidgetIndex(1);

	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance->CheckContainSolvedQuestMap(ItemNum_One))
	{
		ContentWidgetSwitcher->SetActiveWidgetIndex(3);
	}
	else
	{
		ContentWidgetSwitcher->SetActiveWidgetIndex(3);
		GameInstance->AddSolvedQuestMapElement(ItemNum_Two);
		GameInstance->GetUnLockedActorNum(Chapter_Two, Quest_Two, LockNum_Two);
	}

}

void URE_Telegram::Previousbutton_Five_OnClicked()
{
	ContentWidgetSwitcher->SetActiveWidgetIndex(0);
}

void URE_Telegram::Previousbutton_Six_OnClicked()
{
	//ContentWidgetSwitcher->SetActiveWidgetIndex(1);
	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance->CheckContainSolvedQuestMap(ItemNum_One))
	{
		ContentWidgetSwitcher->SetActiveWidgetIndex(5);
	}
	else
	{
		ContentWidgetSwitcher->SetActiveWidgetIndex(5);
		GameInstance->AddSolvedQuestMapElement(ItemNum_Three);
		GameInstance->GetUnLockedActorNum(Chapter_Three, Quest_Three, LockNum_Three);
	}
}


//void URE_Telegram::X_Button_OnClicked()
//{
//	RemoveFromParent();
//}
