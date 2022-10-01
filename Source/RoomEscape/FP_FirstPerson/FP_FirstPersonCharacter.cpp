#include "FP_FirstPersonCharacter.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet\KismetSystemLibrary.h"
#include "RoomEscape\Interaction_Interfece.h"
#include "RoomEscape\RE_PlayerController.h"
#include "RoomEscape\RE_WholeWidget.h"
#include "RoomEscape/RE_GameInstance.h"



AFP_FirstPersonCharacter::AFP_FirstPersonCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0, 0, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;


}


void AFP_FirstPersonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	

	PlayerInputComponent->BindAxis("MoveForward", this, &AFP_FirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFP_FirstPersonCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFP_FirstPersonCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFP_FirstPersonCharacter::LookUpAtRate);


	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFP_FirstPersonCharacter::BindInteract);
	PlayerInputComponent->BindAction("ToggleWholeWidget", IE_Pressed, this, &AFP_FirstPersonCharacter::ToggleWholeWidget);
	PlayerInputComponent->BindAction("ToggleTemp", IE_Pressed, this, &AFP_FirstPersonCharacter::ToggleTemp);

	PlayerInputComponent->BindAction("QuitGame", IE_Pressed, this, &AFP_FirstPersonCharacter::QuitGame);
	PlayerInputComponent->BindAction("Temp", IE_Pressed, this, &AFP_FirstPersonCharacter::ToggleTemp);

	PlayerInputComponent->BindAction("Zero", IE_Pressed, this, &AFP_FirstPersonCharacter::PressZero);
	PlayerInputComponent->BindAction("One", IE_Pressed, this, &AFP_FirstPersonCharacter::PressOne);
	PlayerInputComponent->BindAction("Two", IE_Pressed, this, &AFP_FirstPersonCharacter::PressTwo);
	PlayerInputComponent->BindAction("Three", IE_Pressed, this, &AFP_FirstPersonCharacter::PressThree);
	PlayerInputComponent->BindAction("Four", IE_Pressed, this, &AFP_FirstPersonCharacter::PressFour);
	PlayerInputComponent->BindAction("Five", IE_Pressed, this, &AFP_FirstPersonCharacter::PressFive);
	PlayerInputComponent->BindAction("Six", IE_Pressed, this, &AFP_FirstPersonCharacter::PressSix);
	PlayerInputComponent->BindAction("Seven", IE_Pressed, this, &AFP_FirstPersonCharacter::PressSeven);
	PlayerInputComponent->BindAction("Eight", IE_Pressed, this, &AFP_FirstPersonCharacter::PressEight);
	PlayerInputComponent->BindAction("Nine", IE_Pressed, this, &AFP_FirstPersonCharacter::PressNine);
	
}


void AFP_FirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ARE_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}






void AFP_FirstPersonCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
	
}

void AFP_FirstPersonCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFP_FirstPersonCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFP_FirstPersonCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}





/* Line Trace */
void AFP_FirstPersonCharacter::StartTrace()
{
	FVector StartLocation = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndLocation = (FirstPersonCameraComponent->GetForwardVector() * 600) + StartLocation;


	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);

	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 0.1f);
	//DrawDebugPoint(GetWorld(), Hit.Location, 10.f, FColor::Black, false, 0.f);

	
	if (UKismetSystemLibrary::DoesImplementInterface(Hit.GetActor(), UInteraction_Interfece::StaticClass()))
	{
		// 기존 : nullptr, !nullptr / 신규 : !nullptr
		if (TracedItem != Hit.GetActor() && Hit.GetActor()->IsValidLowLevel())
			TracedItem = Hit.GetActor();
	}
	else
	{
		// 기존 : !nullptr / 신규 : nullptr
		if (TracedItem)
			TracedItem = nullptr;
	}
}

void AFP_FirstPersonCharacter::BindInteract()
{
	StartTrace();

	if (!TracedItem)
		return;

	IInteraction_Interfece* I_Interfece = Cast<IInteraction_Interfece>(TracedItem);
	if (I_Interfece)
	{
		I_Interfece->Interact();
		TracedItem = nullptr;
	}

}






/* Whole Widget */
void AFP_FirstPersonCharacter::ToggleWholeWidget()
{
	PressedItemSlotLocation = -1;

	RE_WholeWidget = CreateWidget<URE_WholeWidget>(GetWorld(), RE_WholeWidgetClass);
	PlayerController->OnCurrentWidgetOffHUD(RE_WholeWidget, EInputMode::EIM_UIOnly);
	PlayerController->ReleaseSlotLocation();
	
}






/* Item Interaction Widget */
void AFP_FirstPersonCharacter::StartInteractionSetting()
{
	DisableInput(PlayerController);
}

void AFP_FirstPersonCharacter::ClearInteractionSetting()
{
	EnableInput(PlayerController);
	PlayerController->SetViewTarget(this);
}






/* Press Item Slot */
void AFP_FirstPersonCharacter::PressZero()
{
	PlayerController->DeliverSlotLocation(0);
	PressedItemSlotLocation = 0;
}

void AFP_FirstPersonCharacter::PressOne()
{
	PlayerController->DeliverSlotLocation(1);
	PressedItemSlotLocation = 1;
}

void AFP_FirstPersonCharacter::PressTwo()
{
	PlayerController->DeliverSlotLocation(2);
	PressedItemSlotLocation = 2;
}

void AFP_FirstPersonCharacter::PressThree()
{
	PlayerController->DeliverSlotLocation(3);
	PressedItemSlotLocation = 3;	
}

void AFP_FirstPersonCharacter::PressFour()
{
	PlayerController->DeliverSlotLocation(4);
	PressedItemSlotLocation = 4;
}

void AFP_FirstPersonCharacter::PressFive()
{
	PlayerController->DeliverSlotLocation(5);
	PressedItemSlotLocation = 5;
}

void AFP_FirstPersonCharacter::PressSix()
{
	PlayerController->DeliverSlotLocation(6);
	PressedItemSlotLocation = 6;
}

void AFP_FirstPersonCharacter::PressSeven()
{
	PlayerController->DeliverSlotLocation(7);
	PressedItemSlotLocation = 7;
}

void AFP_FirstPersonCharacter::PressEight()
{
	PlayerController->DeliverSlotLocation(8);
	PressedItemSlotLocation = 8;
}

void AFP_FirstPersonCharacter::PressNine()
{
	PlayerController->DeliverSlotLocation(9);
	PressedItemSlotLocation = 9;
}

int32 AFP_FirstPersonCharacter::GetPressedItemSlotItemNum()
{
	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
		return -1;

	if (PressedItemSlotLocation == -1)
		return -1;

	return GameInstance->GetSelectedItemSlotNum(PressedItemSlotLocation);
}

int32 AFP_FirstPersonCharacter::GetPressedItemSlotLocation()
{
	return PressedItemSlotLocation;
}






void AFP_FirstPersonCharacter::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
}

void AFP_FirstPersonCharacter::ToggleTemp()
{
	PlayerController->SetInputmodeandCursor(EInputMode::EIM_GameandUI);
}

void AFP_FirstPersonCharacter::RelocationGridPanel()
{
	RE_WholeWidget->RelocationInspectionGridPanel();
}

void AFP_FirstPersonCharacter::SetIntemInspectionPath(int32 PathNum)
{
	RE_WholeWidget->SetItemInspectionPath(PathNum);
}

