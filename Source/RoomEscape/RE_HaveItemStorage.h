#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RE_HaveItemStorage.generated.h"

UCLASS()
class ROOMESCAPE_API ARE_HaveItemStorage : public AActor
{
	GENERATED_BODY()
	
public:	
	ARE_HaveItemStorage();

protected:
	virtual void BeginPlay() override;






protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> ItemSlotClass;


	TArray<class UItemSlot*> TenLimitItemSlotArray;

public:
	int32 GetTenLimitItemSlotArrayNum();
	void SetTenLimitItemSlotArrayElement(UTexture2D* SetTexture, int32 SetItemNum);

};
