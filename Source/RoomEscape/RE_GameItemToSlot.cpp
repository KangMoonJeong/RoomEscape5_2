#include "RE_GameItemToSlot.h"
#include "Components/StaticMeshComponent.h"
#include "Components\SceneComponent.h"
#include "RE_PlayerController.h"
#include "RE_GameInstance.h"
#include "FP_FirstPerson\FP_FirstPersonCharacter.h"
#include "Kismet\GameplayStatics.h"



ARE_GameItemToSlot::ARE_GameItemToSlot()
{
	//PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	Object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Object->SetupAttachment(GetRootComponent());

	AddObject = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AddObjectComponent"));
	AddObject->SetupAttachment(Object);

}

void ARE_GameItemToSlot::BeginPlay()
{
	Super::BeginPlay();

	AddObject->OnClicked.AddDynamic(this, &ARE_GameItemToSlot::AddObjectOnClicked);
}






/* Interact */
void ARE_GameItemToSlot::AddObjectOnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (!RE_GameInstance)
		return;

	AFP_FirstPersonCharacter* PlayerCharacter = Cast<AFP_FirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));


	RE_GameInstance->AddDestroyedItemNumArray(AddObjectItemNum);

	if (RE_GameInstance->SetTenLimitItemSlotArrayElement(AddObjectItemNum))
	{
		RE_GameInstance->SetTenLimitItemSlotDataMap(AddObjectItemNum, true);
	}
	else
	{
		RE_GameInstance->SetOtherLimitItemSlotArrayElement(AddObjectItemNum);
		RE_GameInstance->SetOtherLimitItemSlotDataMap(AddObjectItemNum, true);
	}


	RE_GameInstance->SetNoLimitItemSlotArrayElement(AddObjectItemNum);
	RE_GameInstance->SetNoLimitItemSlotDataMap(AddObjectItemNum, true);

	PlayerCharacter->RelocationGridPanel();

	RE_GameInstance->GetItem(AddObjectItemNum);

	AddObject->DestroyComponent();
}

void ARE_GameItemToSlot::Interact()
{
	URE_GameInstance* RE_GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (!RE_GameInstance)
		return;
	
	ARE_PlayerController* RE_PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!RE_PlayerController)
		return;

	RE_GameInstance->AddDestroyedItemNumArray(ItemNum);

	if (RE_GameInstance->SetTenLimitItemSlotArrayElement(ItemNum))
	{
		RE_GameInstance->SetTenLimitItemSlotDataMap(ItemNum, true);
	}
	else
	{
		RE_GameInstance->SetOtherLimitItemSlotArrayElement(ItemNum);
		RE_GameInstance->SetOtherLimitItemSlotDataMap(ItemNum, true);
	}

	RE_GameInstance->SetNoLimitItemSlotArrayElement(ItemNum);
	RE_GameInstance->SetNoLimitItemSlotDataMap(ItemNum, true);


	RE_PlayerController->AddSlotToHUDItemBarWidget();

	RE_GameInstance->GetItem(ItemNum);


	SetActorEnableCollision(false);
	//Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Destroy();
}






/* Get Data */
int ARE_GameItemToSlot::GetItemNum()
{
	return ItemNum;
}

int32 ARE_GameItemToSlot::GetAddObjectItemNum()
{
	return AddObjectItemNum;
}






/* Destroy Add Object*/
void ARE_GameItemToSlot::DestroyAddObject()
{
	AddObject->DestroyComponent();
}
