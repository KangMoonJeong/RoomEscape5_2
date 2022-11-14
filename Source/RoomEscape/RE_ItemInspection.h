#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inspection_Interface.h"
#include "ItemSlotInteraction_Interface.h"
#include "RE_ItemInspection.generated.h"

UCLASS(Config=Game)
class ROOMESCAPE_API ARE_ItemInspection : public AActor, public IInspection_Interface, public IItemSlotInteraction_Interface
{
	GENERATED_BODY()
	
public:	
	ARE_ItemInspection();

protected:
	virtual void BeginPlay() override;



protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(Config)
	TArray<FSoftObjectPath> GameItemSoftObjectPath;

	UPROPERTY(EditAnywhere)
	class AActor* Camera;

	UPROPERTY(EditAnywhere)
	float MoveForwardMaxZoom = -30.f;

	UPROPERTY(EditAnywhere)
	float MoveForwardMinZoom;

	UPROPERTY(EditAnywhere)
	FVector StartLocation;

	FVector CurrentLocation;

	FVector InitialChildActorLocation;

	TArray<int32> DestroyedArray;

	float MoveForwardZoom;

	class ARE_GameItemToSlot* SpawnActor = nullptr;





	/* Set ChildActor Class */
public:
	void SpawnGameItemToSlotActor();
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



private:
	UPROPERTY(EditAnywhere)
	TArray<FString> ItemPaths;
};
