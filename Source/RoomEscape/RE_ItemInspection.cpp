#include "RE_ItemInspection.h"
#include "Components\SceneComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components\SceneCaptureComponent2D.h"
#include "Components\InputComponent.h"
#include "RE_GameItemToSlot.h"
#include "Kismet/KismetMathLibrary.h"
#include "RE_PlayerController.h"
#include "RE_GameInstance.h"
#include "GameItemToSlot_Interface.h"
#include  "Kismet\GameplayStatics.h"


ARE_ItemInspection::ARE_ItemInspection()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

}

void ARE_ItemInspection::BeginPlay()
{
	Super::BeginPlay();

	SpawnGameItemToSlotActor();
	InitialChildActorLocation = StartLocation;
}




void ARE_ItemInspection::SpawnGameItemToSlotActor()
{
	FString GameItemPath = "Blueprint'" + GameItemSoftObjectPath[2].GetAssetPathString() + "_C'";
	UClass* GameItemClass = LoadClass<ARE_GameItemToSlot>(this, *GameItemPath);
}


/* Set ChildActor Class */
void ARE_ItemInspection::StartInteractionSetting()
{
	ARE_PlayerController* PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->SetViewTarget(Camera);

	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	DestroyedArray = GameInstance->GetDestroyedItemNumArray();

	SetInputComponent();
}

void ARE_ItemInspection::ClearInteractionSetting()
{
	DisableInput(GetWorld()->GetFirstPlayerController());
}

void ARE_ItemInspection::SetChildActorClassFromPath(int32 ItemNum)
{
	if (ItemNum < 1)
		return;

	if (SpawnActor != nullptr)
	{
		SpawnActor->Destroy();
		SpawnActor = nullptr;
	}
	//FString GameItemPath = "Blueprint'" + GameItemSoftObjectPath[ItemNum].GetAssetPathString() + "_C'";
	//UE_LOG(LogTemp, Warning, TEXT("GameItemPath : %s"), *GameItemPath);
	UClass* GameItemClass = LoadClass<ARE_GameItemToSlot>(this, *ItemPaths[ItemNum]);
	SpawnActor = GetWorld()->SpawnActor<ARE_GameItemToSlot>(GameItemClass, StartLocation, FRotator(0.f));
	MoveForwardZoom = 0.f;
	CurrentLocation = StartLocation;


	/*if (DestroyedArray.Contains(SpawnActor->GetAddObjectItemNum()))
		SpawnActor->DestroyAddObject();*/


}


void ARE_ItemInspection::ItemSlotOnClikced(int32 ItemNum)
{
	UE_LOG(LogTemp, Warning, TEXT("ARE_ItemInspection::ItemSlotOnClikced(int32 ItemNum)"))

}






/* Set ChildActor Movable*/
void ARE_ItemInspection::SetInputComponent()
{
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		InputComponent->BindAxis("MoveForward", this, &ARE_ItemInspection::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &ARE_ItemInspection::MoveRight);
		InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ARE_ItemInspection::ZoomIn);
		InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ARE_ItemInspection::ZoomOut);
		
		//InputComponent->
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void ARE_ItemInspection::MoveForward(float Value)
{
	if (Value != 0)
	{
		FRotator ChildActorRotator(0.f, 0.f, (Value * -3.0));
		SpawnActor->SetActorRotation(UKismetMathLibrary::ComposeRotators(SpawnActor->GetActorRotation(), ChildActorRotator));
	}
}

void ARE_ItemInspection::MoveRight(float Value)
{
	if (Value != 0)
	{
		FRotator ChildActorRotator(0.f, (Value * 3.0), 0.f);
		SpawnActor->AddActorWorldRotation(ChildActorRotator);
	}
}

void ARE_ItemInspection::ZoomIn()
{
	if (MoveForwardZoom <= MoveForwardMaxZoom)
		return;


	CurrentLocation = SpawnActor->GetActorLocation();
	CurrentLocation += FVector(0.f, -2.f, 0.f);
	SpawnActor->SetActorLocation(CurrentLocation);

	MoveForwardZoom -= 2.0f;
}

void ARE_ItemInspection::ZoomOut()
{
	if (MoveForwardZoom >= MoveForwardMinZoom)
		return;

	CurrentLocation = SpawnActor->GetActorLocation();
	CurrentLocation += FVector(0.f, 2.f, 0.f);
	SpawnActor->SetActorLocation(CurrentLocation);
	MoveForwardZoom += 2.0f;
}

