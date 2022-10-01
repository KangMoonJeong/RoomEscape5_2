#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimeLineComponent.h"
#include "Door.generated.h"

UCLASS()
class ROOMESCAPE_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* LeftDoor;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RightDoor;
	



public:
	FTimeline TimeLine;


	UFUNCTION()
	void LeftDoorRotation(float Value);

	UFUNCTION()
	void RightDoorRotation(float Value);


};
