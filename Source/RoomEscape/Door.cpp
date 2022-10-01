#include "Door.h"
#include "Components/StaticMeshComponent.h"


ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	LeftDoor->SetupAttachment(GetRootComponent());

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	RightDoor->SetupAttachment(GetRootComponent());







	FOnTimelineFloat progressFunction_Left{};
	progressFunction_Left.BindUFunction(this, "LeftDoorRotation"); 

	FOnTimelineFloat progressFunction_Right{};
	progressFunction_Right.BindUFunction(this, "RightDoorRotation"); 
	

	const ConstructorHelpers::FObjectFinder<UCurveFloat> LeftDoor_Curve(TEXT("CurveFloat'/Game/707/Door/LeftDoor_Curve.LeftDoor_Curve'"));
	const ConstructorHelpers::FObjectFinder<UCurveFloat> RightDoor_Curve(TEXT("CurveFloat'/Game/707/Door/RightDoor_Curve.RightDoor_Curve'"));
	TimeLine = FTimeline{};
	
	TimeLine.AddInterpFloat(LeftDoor_Curve.Object, progressFunction_Left, FName{TEXT("LEFT_Door")});
	TimeLine.AddInterpFloat(RightDoor_Curve.Object, progressFunction_Right, FName{ TEXT("RIGHT_Door") });

}


void ADoor::BeginPlay()
{
	Super::BeginPlay();

	TimeLine.Play();
	
}


void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimeLine.IsPlaying())
	{
		TimeLine.TickTimeline(DeltaTime);
	}
}

void ADoor::RightDoorRotation(float Value)
{
	RightDoor->SetRelativeRotation(FRotator(0, Value, 0)); // 180
}

void ADoor::LeftDoorRotation(float Value)
{
	LeftDoor->SetRelativeRotation(FRotator(0, Value, 0)); // 0
	
}
