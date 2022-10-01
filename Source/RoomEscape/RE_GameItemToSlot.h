#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction_Interfece.h"
#include "GameItemToSlot_Interface.h"
#include "RE_GameItemToSlot.generated.h"

UCLASS()
class ROOMESCAPE_API ARE_GameItemToSlot : public AActor, public IInteraction_Interfece, public IGameItemToSlot_Interface
{
	GENERATED_BODY()
	
public:	
	ARE_GameItemToSlot();

protected:
	virtual void BeginPlay() override;






protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Object;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* AddObject;

	UPROPERTY(EditAnywhere)
	class UTexture2D* SlotImage;

	UPROPERTY(EditAnywhere)
	int32 ItemNum;

	UPROPERTY(EditAnywhere)
	int32 AddObjectItemNum;






	/* Interact */
protected:
	UFUNCTION()
	void AddObjectOnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	void Interact() override;
	




	/* Get Data */
protected:
	int GetItemNum() override;
public:
	int32 GetAddObjectItemNum();





	/* Destroy Add Object*/
public:
	void DestroyAddObject();
};
