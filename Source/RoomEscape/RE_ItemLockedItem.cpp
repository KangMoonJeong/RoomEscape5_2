#include "RE_ItemLockedItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "FP_FirstPerson\FP_FirstPersonCharacter.h"
#include "Kismet\GameplayStatics.h"
#include "RE_GameInstance.h"
#include "ItemSlot.h"
#include "RE_PlayerController.h"


ARE_ItemLockedItem::ARE_ItemLockedItem()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	LeftDoor->SetupAttachment(GetRootComponent());

	RightDoor= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	RightDoor->SetupAttachment(GetRootComponent());

	InteractBound = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBound"));
	InteractBound->SetupAttachment(GetRootComponent());






	/* TimeLine*/

	FOnTimelineFloat progressFunction_Left{};
	progressFunction_Left.BindUFunction(this, "LeftDoorRotation");

	FOnTimelineFloat progressFunction_Right{};
	progressFunction_Right.BindUFunction(this, "RightDoorRotation");

	FOnTimelineEvent TimelineFinishEvent; 
	TimelineFinishEvent.BindUFunction(this, "TimeLineFinish");

	
	const ConstructorHelpers::FObjectFinder<UCurveFloat> RightDoor_Curve(TEXT("CurveFloat'/Game/707/Door/LeftDoor_Curve.LeftDoor_Curve'"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat> LeftDoor_Curve(TEXT("CurveFloat'/Game/707/Door/RightDoor_Curve.RightDoor_Curve'"));
	TimeLine = FTimeline{};

	TimeLine.AddInterpFloat(LeftDoor_Curve.Object, progressFunction_Left, FName{ TEXT("LEFT_Door") });
	TimeLine.AddInterpFloat(RightDoor_Curve.Object, progressFunction_Right, FName{ TEXT("RIGHT_Door") });
	TimeLine.SetTimelineFinishedFunc(TimelineFinishEvent);

}

void ARE_ItemLockedItem::BeginPlay()
{
	Super::BeginPlay();

	InteractBound->OnComponentBeginOverlap.AddDynamic(this, &ARE_ItemLockedItem::InteractBoundBeginOverlap);
	InteractBound->OnComponentEndOverlap.AddDynamic(this, &ARE_ItemLockedItem::InteractBoundEndOverlap);
}

void ARE_ItemLockedItem::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

	if (TimeLine.IsPlaying())
		TimeLine.TickTimeline(DeltaTime);

}

void ARE_ItemLockedItem::InteractBoundBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && !bEverSolveLock)
	{
		AFP_FirstPersonCharacter* Character = Cast<AFP_FirstPersonCharacter>(OtherActor);
		if (Character)
			bInInteractBound = true;
	}
}

void ARE_ItemLockedItem::InteractBoundEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && !bEverSolveLock)
	{
		AFP_FirstPersonCharacter* Character = Cast<AFP_FirstPersonCharacter>(OtherActor);
		if (Character)
			bInInteractBound = false;
	}
}



/* Interact */
void ARE_ItemLockedItem::Interact()
{
	if (!bInInteractBound && bEverSolveLock)
		return;

	AFP_FirstPersonCharacter* Character = Cast<AFP_FirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	int32 GetItemNum = Character->GetPressedItemSlotItemNum();
	SelectTenLimitIndex = Character->GetPressedItemSlotLocation();

	if (GetItemNum == LockedItemNum)
	{
		UE_LOG(LogTemp, Warning, TEXT("1111 TimeLine.Play();"))
		TimeLine.Play();
		UE_LOG(LogTemp, Warning, TEXT("2222 TimeLine.Play();"))

	}
}






/* TimeLine */
void ARE_ItemLockedItem::LeftDoorRotation(float Value)
{
	if (bRight)
	{
		if (bSlide)
		{
			RightDoor->SetRelativeLocation(FVector(Value, 0, 0));
		}
		else
		{
			RightDoor->SetRelativeRotation(FRotator(0, Value, 0)); // 180
		}
	}
}

void ARE_ItemLockedItem::RightDoorRotation(float Value)
{
	if (bLeft)
	{
		if (bSlide)
		{
			LeftDoor->SetRelativeLocation(FVector(Value, 0, 0));
		}
		else
		{
			LeftDoor->SetRelativeRotation(FRotator(0, Value, 0)); // 0
		}
	}
}

void ARE_ItemLockedItem::TimeLineFinish()
{
	SetActorTickEnabled(false);


	SolevedItem();

	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
		return;

	GameInstance->GetUnLockedActorNum(Chapter, Quest, LockNum);
	GameInstance->DeleteTenLimitArrayElementByIndex(SelectTenLimitIndex);
	GameInstance->DeleteNoLimitArrayElementByIndex(SelectTenLimitIndex);

	ARE_PlayerController* Controller = Cast<ARE_PlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->GetHUDInitializeSlotBar();
}





/* Save Solved Status */
void ARE_ItemLockedItem::SolevedItem()
{
	bEverSolveLock = true;

	if (bSlide)
	{
		LeftDoor->SetRelativeLocation(LeftDoorLocation);
		RightDoor->SetRelativeLocation(RightDoorLocation);
	}
	else
	{
		LeftDoor->SetRelativeRotation(LeftDoorRotator);
		RightDoor->SetRelativeRotation(RightDoorRotator);

	}

	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	GameInstance->AddSolvedQuestMapElement(ItemNum);
}





/* Get Data */
int32 ARE_ItemLockedItem::GetItemNum()
{
	return ItemNum;
}

