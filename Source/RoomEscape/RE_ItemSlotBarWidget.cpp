#include "RE_ItemSlotBarWidget.h"
#include "Components\Border.h"
#include "RE_GameInstance.h"
#include "ItemSlot.h"

bool URE_ItemSlotBarWidget::Initialize()
{
	if (!Super::Initialize())
		return false;


	return true;
}





/* Add Slot Element */
void URE_ItemSlotBarWidget::AddTenLimitItemSlotElement()
{
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (RE_GameInstance->GetTenLimitItemSlotArrayNum() == 11)
		return;

	TArray<class UItemSlot*> TenLimitItemSlotArray;
	TenLimitItemSlotArray = RE_GameInstance->GetTenLimitItemSlotArray();

	switch (RE_GameInstance->GetTenLimitItemSlotArrayNum() -1)
	{
	case 0:
	{
		Border_0->AddChild(TenLimitItemSlotArray[0]);
		UE_LOG(LogTemp, Warning, TEXT("Border 0"))

		break;
	}
	case 1:
	{
		Border_1->AddChild(TenLimitItemSlotArray[1]);
		UE_LOG(LogTemp, Warning, TEXT("Border 1"))

		break;
	}
	case 2:
	{
		Border_2->AddChild(TenLimitItemSlotArray[2]);
		UE_LOG(LogTemp, Warning, TEXT("Border 2"))

		break;
	}
	case 3:
	{
		Border_3->AddChild(TenLimitItemSlotArray[3]);
		UE_LOG(LogTemp, Warning, TEXT("Border 3"))

		break;
	}
	case 4:
	{
		Border_4->AddChild(TenLimitItemSlotArray[4]);
		UE_LOG(LogTemp, Warning, TEXT("Border 4"))

		break;
	}
	case 5:
	{
		Border_5->AddChild(TenLimitItemSlotArray[5]);
		UE_LOG(LogTemp, Warning, TEXT("Border 5"))

		break;
	}
	case 6:
	{
		Border_6->AddChild(TenLimitItemSlotArray[6]);
		UE_LOG(LogTemp, Warning, TEXT("Border 6"))

		break;
	}
	case 7:
	{
		Border_7->AddChild(TenLimitItemSlotArray[7]);
		UE_LOG(LogTemp, Warning, TEXT("Border 7"))

		break;
	}
	case 8:
	{
		Border_8->AddChild(TenLimitItemSlotArray[8]);
		UE_LOG(LogTemp, Warning, TEXT("Border 8"))
		break;
	}
	case 9:
	{
		Border_9->AddChild(TenLimitItemSlotArray[9]);
		UE_LOG(LogTemp, Warning, TEXT("Border 9"))

		break;
	}
	default:
	{
		UE_LOG(LogTemp, Warning, TEXT("URE_ItemSlotBarWidget::CreateItemSlot() : Default"))
		break;
	}
	}

}





/* When Load Game, Open InventoryWidget from WholeWidget*/
void URE_ItemSlotBarWidget::InitializeSlot()
{
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (RE_GameInstance->GetTenLimitItemSlotArrayNum() == 0)
		return;

	TArray<class UItemSlot*> TenLimitItemSlotArray;
	TenLimitItemSlotArray = RE_GameInstance->GetTenLimitItemSlotArray();

	for (int32 i = 0; i < TenLimitItemSlotArray.Num(); i++)
	{
		switch (i)
		{
		case 0:
		{
			Border_0->AddChild(TenLimitItemSlotArray[0]);
			break;
		}
		case 1:
		{
			Border_1->AddChild(TenLimitItemSlotArray[1]);
			break;
		}
		case 2:
		{
			Border_2->AddChild(TenLimitItemSlotArray[2]);

			break;
		}
		case 3:
		{
			Border_3->AddChild(TenLimitItemSlotArray[3]);
			break;
		}
		case 4:
		{
			Border_4->AddChild(TenLimitItemSlotArray[4]);

			break;
		}
		case 5:
		{
			Border_5->AddChild(TenLimitItemSlotArray[5]);

			break;
		}
		case 6:
		{
			Border_6->AddChild(TenLimitItemSlotArray[6]);

			break;
		}
		case 7:
		{
			Border_7->AddChild(TenLimitItemSlotArray[7]);

			break;
		}
		case 8:
		{
			Border_8->AddChild(TenLimitItemSlotArray[8]);

			break;
		}
		case 9:
		{
			Border_9->AddChild(TenLimitItemSlotArray[9]);

			break;
		}
		default:
		{
			UE_LOG(LogTemp, Warning, TEXT("URE_ItemSlotBarWidget::InitializeSlot() : Default"))
				break;
		}
		}
	}
}





/* Press Item Slot */
void URE_ItemSlotBarWidget::PressItemSlot(int32 PressLocation)
{
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());

	TArray<class UItemSlot*> TenLimitItemSlotArray;
	TenLimitItemSlotArray = RE_GameInstance->GetTenLimitItemSlotArray();

	if (PressedLocation != -1 && TenLimitItemSlotArray.IsValidIndex(PressedLocation))
		TenLimitItemSlotArray[PressedLocation]->PressedImageToHidden();


	if (TenLimitItemSlotArray.IsValidIndex(PressLocation))
	{
		TenLimitItemSlotArray[PressLocation]->PressedImageToVisible();
		PressedLocation = PressLocation;
	}
}

void URE_ItemSlotBarWidget::ReleaseItemSlot()
{
	if (PressedLocation == -1)
		return;

	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());

	TArray<class UItemSlot*> TenLimitItemSlotArray;
	TenLimitItemSlotArray = RE_GameInstance->GetTenLimitItemSlotArray();

	if (!TenLimitItemSlotArray.IsValidIndex(PressedLocation))
		return;

	TenLimitItemSlotArray[PressedLocation]->PressedImageToHidden();
	PressedLocation = -1;
}