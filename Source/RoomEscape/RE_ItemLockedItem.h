#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction_Interfece.h"
#include "LockedItem_Interface.h"
#include "Components/TimeLineComponent.h"
#include "RE_ItemLockedItem.generated.h"

UCLASS()
class ROOMESCAPE_API ARE_ItemLockedItem : public AActor, public IInteraction_Interfece, public ILockedItem_Interface
{
	GENERATED_BODY()
	
public:	
	ARE_ItemLockedItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* LeftDoor;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RightDoor;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* InteractBound;

	UPROPERTY(EditAnywhere)
	int32 LockedItemNum = 0;

	UPROPERTY(EditAnywhere)
	int32 ItemNum = 0;

	UPROPERTY(EditAnywhere)
	int32 Chapter;

	UPROPERTY(EditAnywhere)
	int32 Quest;

	UPROPERTY(EditAnywhere)
	int32 LockNum;

	UPROPERTY(EditAnywhere)
	FRotator LeftDoorRotator;

	UPROPERTY(EditAnywhere)
	FRotator RightDoorRotator;

	UPROPERTY(EditAnywhere)
	FVector LeftDoorLocation;

	UPROPERTY(EditAnywhere)
	FVector RightDoorLocation;

	FTimeline TimeLine;
	
	int32 SelectTenLimitIndex = -1;


	bool bInInteractBound = false;

	bool bEverSolveLock = false;





protected:
	UFUNCTION()
	virtual void InteractBoundBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void InteractBoundEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);







	/* Interact */
public:
	void Interact() override;




	
	/* TimeLine */
protected:
	UFUNCTION()
	void LeftDoorRotation(float Value);

	UFUNCTION()
	void RightDoorRotation(float Value);

	UFUNCTION()
	void TimeLineFinish();






	/* Save Solved Status */
public:
	UFUNCTION()
	void SolevedItem() override;





	/* Get Data */
public:
	int32 GetItemNum() override;



	

	UPROPERTY(EditAnywhere)
	bool bSlide;

	UPROPERTY(EditAnywhere)
	bool bLeft;

	UPROPERTY(EditAnywhere)
	bool bRight;


	void SetDoorRotation(float DeltaTime);
	bool CanRotation = false;
	float CurrntLeftRotation = 0.f;
	float CurrntRightRotation = 180.f;

	void SolvedQuest();
};
