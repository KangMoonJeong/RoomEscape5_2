#include "RE_PasswordLockedItem.h"
#include "FourDigitPasswordWidget.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework\Character.h"
#include "RE_GameInstance.h"


ARE_PasswordLockedItem::ARE_PasswordLockedItem()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(GetRootComponent());

	WidgetBound = CreateDefaultSubobject<UBoxComponent>(TEXT("WidgetBound"));
	WidgetBound->SetupAttachment(GetRootComponent());

	bEverSolveLock = false;

}

void ARE_PasswordLockedItem::BeginPlay()
{
	Super::BeginPlay();
	WidgetBound->OnComponentBeginOverlap.AddDynamic(this, &ARE_PasswordLockedItem::WidgetBoundBeginOverlap);
	WidgetBound->OnComponentEndOverlap.AddDynamic(this, &ARE_PasswordLockedItem::WidgetBoundEndOverlap);
}

void ARE_PasswordLockedItem::WidgetBoundBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && !bEverSolveLock)
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (Character)
			bCanOpenWidget = true;

	}
}

void ARE_PasswordLockedItem::WidgetBoundEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && !bEverSolveLock)
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (Character)
			bCanOpenWidget = false;
	}
}

void ARE_PasswordLockedItem::Interact()
{
	if (bEverSolveLock || !bCanOpenWidget)
		return;

	if (bFourDigitPassword)
	{
		FourDigitPasswordWidget = CreateWidget<UFourDigitPasswordWidget>(GetWorld(), FourDigitPasswordWidgetClass);
		FourDigitPasswordWidget->SetLockedItem(this);
	}
}

void ARE_PasswordLockedItem::SolevedItem()
{
	bEverSolveLock = true;
	URE_GameInstance* GameInstance = Cast<URE_GameInstance>(GetWorld()->GetGameInstance());
	GameInstance->AddSolvedQuestMapElement(ItemNum);
	UE_LOG(LogTemp, Warning, TEXT("ARE_PasswordLockedItem::SolevedItem()"));
}

int32 ARE_PasswordLockedItem::GetItemNum()
{
	return ItemNum;
}


