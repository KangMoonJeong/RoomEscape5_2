#include "RE_CameraInspectionActor.h"
#include "RE_PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components\SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components\InputComponent.h"
#include "RE_GameItemToSlot.h"



ARE_CameraInspectionActor::ARE_CameraInspectionActor()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void ARE_CameraInspectionActor::BeginPlay()
{
	Super::BeginPlay();
	SpawnItemActor();
	SetChildActorClassFromPath(2);
}


void ARE_CameraInspectionActor::StartInteractionSetting()
{
	ARE_PlayerController* PlayerController = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->SetViewTarget(Camera1);

	SetInputComponent();
}


void ARE_CameraInspectionActor::ClearInteractionSetting()
{
	DisableInput(GetWorld()->GetFirstPlayerController());
}

void ARE_CameraInspectionActor::SetChildActorClassFromPath(int32 ItemNum)
{
	/*FString GameItemPath = "Blueprint'" + GameItemSoftObjectPath[2].GetAssetPathString() + "_C'";
	UClass* GameItemClass = LoadClass<ARE_GameItemToSlot>(this, *GameItemPath);
	SpawnItem->LoadedFromAnotherClass(GameItemClass->GetFName());*/

}
void ARE_CameraInspectionActor::ItemSlotOnClikced(int32 ItemNum)
{
}

void ARE_CameraInspectionActor::SetInputComponent()
{
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		InputComponent->BindAxis("MoveForward", this, &ARE_CameraInspectionActor::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &ARE_CameraInspectionActor::MoveRight);
		InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ARE_CameraInspectionActor::ZoomIn);
		InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ARE_CameraInspectionActor::ZoomOut);

		//InputComponent->
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void ARE_CameraInspectionActor::MoveForward(float Value)
{
}

void ARE_CameraInspectionActor::MoveRight(float Value)
{
}

void ARE_CameraInspectionActor::ZoomIn()
{
}

void ARE_CameraInspectionActor::ZoomOut()
{
}

void ARE_CameraInspectionActor::SpawnItemActor()
{
	SpawnItem = GetWorld()->SpawnActor<ARE_GameItemToSlot>(ARE_GameItemToSlot::StaticClass(), StartLocation, FRotator(0.f));
}
