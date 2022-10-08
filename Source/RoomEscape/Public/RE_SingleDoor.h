#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimeLineComponent.h"
#include "RoomEscape\Interaction_Interfece.h"
#include "RE_SingleDoor.generated.h"

UCLASS()
class ROOMESCAPE_API ARE_SingleDoor : public AActor, public IInteraction_Interfece
{
	GENERATED_BODY()
	
public:	
	ARE_SingleDoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;



private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* LeftDoor;



public:
	FTimeline TimeLine;


	UFUNCTION()
	void LeftDoorRotation(float Value);


protected:
	void Interact() override;





	UPROPERTY(EditAnywhere)
	bool bSlide;

	UPROPERTY(EditAnywhere)
	bool bLeft;

	UPROPERTY(EditAnywhere)
	bool bRight;


};
