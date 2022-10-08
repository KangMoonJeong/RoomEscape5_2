#include "RE_SingleDoor.h"
#include "Components/StaticMeshComponent.h"



ARE_SingleDoor::ARE_SingleDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	LeftDoor->SetupAttachment(GetRootComponent());

	FOnTimelineFloat progressFunction_Left{};
	progressFunction_Left.BindUFunction(this, "LeftDoorRotation");


	const ConstructorHelpers::FObjectFinder<UCurveFloat> LeftDoor_Curve(TEXT("CurveFloat'/Game/707/Door/LeftDoor_Curve.LeftDoor_Curve'"));

	TimeLine = FTimeline{};

	TimeLine.AddInterpFloat(LeftDoor_Curve.Object, progressFunction_Left, FName{ TEXT("LEFT_Door") });


}

void ARE_SingleDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARE_SingleDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimeLine.IsPlaying())
	{
		TimeLine.TickTimeline(DeltaTime);
	}

}

void ARE_SingleDoor::LeftDoorRotation(float Value)
{
	if (bLeft)
	{
		if (bSlide)
		{
			LeftDoor->SetRelativeLocation(FVector(0, Value, 0));
		}
		else
		{
			LeftDoor->SetRelativeRotation(FRotator(0, Value, 0)); // 0
		}

	}
}

void ARE_SingleDoor::Interact()
{
	TimeLine.Play();
}

