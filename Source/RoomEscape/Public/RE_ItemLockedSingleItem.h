#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "RoomEscape\Interaction_Interfece.h"
//#include "RoomEscape\LockedItem_Interface.h"
#include "Components/TimeLineComponent.h"
#include "RE_ItemLockedSingleItem.generated.h"

UCLASS()
class ROOMESCAPE_API ARE_ItemLockedSingleItem : public AActor
	//, public IInteraction_Interfece, public ILockedItem_Interface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARE_ItemLockedSingleItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
