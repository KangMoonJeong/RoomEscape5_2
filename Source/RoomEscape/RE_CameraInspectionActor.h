#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inspection_Interface.h"
#include "ItemSlotInteraction_Interface.h"
#include "RE_CameraInspectionActor.generated.h"

UCLASS(Config = Game)
class ROOMESCAPE_API ARE_CameraInspectionActor : public AActor, public IInspection_Interface, public IItemSlotInteraction_Interface
{
	GENERATED_BODY()
	
public:	
	ARE_CameraInspectionActor();

protected:
	virtual void BeginPlay() override;


protected:

	UPROPERTY(Config)
	TArray<FSoftObjectPath> GameItemSoftObjectPath;

	FVector InitialChildActorLocation;

	float MoveForwardZoom;

	float MoveForwardMaxZoom = -30.f;

	UPROPERTY(EditAnywhere)
	class AActor* Camera1;


	/* Set ChildActor Class */
public:
	void StartInteractionSetting()  override;
	void ClearInteractionSetting() override;
	void SetChildActorClassFromPath(int32 ItemNum) override;
	void ItemSlotOnClikced(int32 ItemNum) override;



	/* Set ChildActor Movable*/
protected:
	void SetInputComponent();

	void MoveForward(float Value);
	void MoveRight(float Value);
	void ZoomIn();
	void ZoomOut();



	void SpawnItemActor();
	class ARE_GameItemToSlot* SpawnItem;

	UPROPERTY(EditAnywhere)
	FVector StartLocation;

};
